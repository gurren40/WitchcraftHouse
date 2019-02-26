#include "usercontroller.h"
#include "Control/devicecontroller.h"
#include "Control/schedulecontroller.h"
#include "Control/sharedcontroller.h"

UserController::UserController(QObject *parent) : QObject(parent)
{

}

UserController::UserController(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void UserController::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

void UserController::setSecret(QString secret)
{
    this->secret = secret;
}

bool UserController::isJwtValid(QJsonObject jwt, QString path)
{
    if(path == "/control"){
        if(jwt["iss"].toString() != "WitchcraftHouse") return false;
        User user(&db);
        user.read("email='"+jwt["aud"].toString()+"'");
        if(user.mUsers.size() != 1) return false;
        ControllDevice cd(&db);
        cd.read("controlDeviceID=UuidToBin('"+jwt["jti"].toString()+"')");
        if(cd.mControlDevices.size() != 1) return  false;
        QDateTime dt(cd.mControlDevices.at(0).expireDate);
        if(dt.toSecsSinceEpoch() > jwt["exp"].toString().toInt()) return false;
        if(cd.mControlDevices.at(0).isControlDeviceOnline) return false;
        if(!toggleControlDeviceOnline(cd.mControlDevices.at(0).controlDeviceID,true)) return false;
    }
    else {
        return false;
    }
    return  true;
}

bool UserController::toggleControlDeviceOnline(QUuid controlDeviceID, bool toggle)
{
    ControllDevice device(&db);
    device.read("controlDeviceID=UuidToBin('"+controlDeviceID.toString(QUuid::WithoutBraces)+"')");
    if(device.mControlDevices.size() != 1){
        return false;
    }
    if(device.mControlDevices.at(0).isControlDeviceOnline == toggle){
        return false;
    }
    controlDevice dvc = device.mControlDevices.at(0);
    device.update(dvc.controlDeviceID,dvc.userID,dvc.controlDeviceName,dvc.controlDeviceToken,toggle,dvc.expireDate);
    return true;
}

QJsonObject UserController::selectAllControlDevice(int userID)
{
    QJsonObject response;
    QJsonArray responseArray;
    ControllDevice cdv(&db);
    cdv.read("userID='"+QString::number(userID)+"'");

    //kalau ga ada device dengan userID yang sesuai
    if(cdv.mControlDevices.size()<1){
        QJsonObject error;
        error["error"] = "the user has no control device registered";
        error["errorCode"] = "5";
        responseArray.append(error);
        response["error"] = responseArray;
        return response;
    }
    else {
        for (int i = 0;i<cdv.mControlDevices.size();i++) {
            QJsonObject controlDeviceObject;
            controlDeviceObject["controlDeviceID"]= cdv.mControlDevices.at(i).controlDeviceID.toString(QUuid::WithoutBraces);
            controlDeviceObject["userID"]= cdv.mControlDevices.at(i).userID;
            controlDeviceObject["userName"]= cdv.mControlDevices.at(i).userName;
            controlDeviceObject["controlDeviceName"]= cdv.mControlDevices.at(i).controlDeviceName;
            controlDeviceObject["controlDeviceToken"]= cdv.mControlDevices.at(i).controlDeviceToken;
            controlDeviceObject["isControlDeviceOnline"]= cdv.mControlDevices.at(i).isControlDeviceOnline;
            controlDeviceObject["expireDate"]= cdv.mControlDevices.at(i).expireDate.toString();
            responseArray.append(controlDeviceObject);
        }
        response["controlDevice"] = responseArray;
        return response;
    }
}

int UserController::getUserIDByControlDeviceID(QUuid controlDeviceID)
{
    ControllDevice cd(&db);
    cd.read("controlDeviceID=(UuidToBin('"+controlDeviceID.toString(QUuid::WithoutBraces)+"')");
    if(cd.mControlDevices.size()!=1){
        return 0;
    }
    else{
        return cd.mControlDevices.at(0).userID;
    }
}

QString UserController::QUuidToQString(QUuid UUID)
{
    return UUID.toString(QUuid::WithoutBraces);
}

QUuid UserController::QStringToQUuid(QString string)
{
    QUuid UUID(string);
    return UUID;
}

QJsonObject UserController::createUser(QJsonObject json)
{
    QJsonObject response;
    QJsonArray errorArray;
    QJsonArray notificationArray;
    User user(&db);
    QJsonArray jsonArray = json["createNewUser"].toArray();
    for (int i=0;i<jsonArray.size();i++) {
        QJsonObject jsonObject = jsonArray[i].toObject();
        //check kalau apakah email sudah digunakan.
        QJsonObject readError = user.read("email='"+jsonObject["email"].toString()+"'");
        if(readError["error"].toString()!="0"){
            QJsonObject errorValue;
            QJsonObject notificationValue;
            errorValue["error"] = readError["error"].toString();
            errorValue["errorCode"] = "2";
            notificationValue["title"] = "Error";
            notificationValue["description"] = errorValue["error"].toString();
            errorArray.append(errorValue);
            notificationArray.append(notificationValue);
        }
        else {
            QCryptographicHash passHash(QCryptographicHash::Sha256);
            passHash.addData(jsonObject["password"].toString().toUtf8());

            //buat user baru
            QJsonObject errorValue = user.create(jsonObject["email"].toString(),QString::fromUtf8(passHash.result().toHex()),jsonObject["name"].toString());
            QJsonObject notificationValue;
            if(errorValue["error"].toString() == "0"){
                notificationValue["title"] = "User has been created";
                notificationValue["description"] = "User with email "+jsonObject["email"].toString()+" has been created\nPlease login with your email and password";
                QString title = "User Has Been Created";
                QString body = "Thankyou "+jsonObject["name"].toString()+".\nYou have created account with this email\nplease do not reveal your password to anyone\nThank you";
                emit sendMail(jsonObject["email"].toString(),title,body);
                Log log(&db);
                user.read("email='"+jsonObject["email"].toString()+"'");
                log.create(user.mUsers.at(0).userID,"User with email "+jsonObject["email"].toString()+" has been created");
            }
            else {
                notificationValue["title"] = "Error";
                notificationValue["description"] = errorValue["error"].toString();
            }
            errorArray.append(errorValue);
            notificationArray.append(notificationValue);
        }
    }
    response["error"]=errorArray;
    response["notification"]=notificationArray;
    return  response;
}

QJsonObject UserController::requestLoginToken(QJsonObject json)
{
    QJsonObject response;
    QJsonArray jsonArray = json["requestLoginToken"].toArray();
    User user(&db);
    ControllDevice controlDevice(&db);
    QUuid controlDeviceID = QUuid::createUuid();
    QDateTime today = QDateTime::currentDateTimeUtc();

    //check kalo di array hanya ada 1 data
    if(jsonArray.size() != 1){
        QJsonArray errorArray,notificationArray;
        QJsonObject error,notification;
        error["error"] = "No data has requested or bulk data recivied";
        error["errorCode"] = "3";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
        response["error"] = errorArray;
        response["notification"] = notificationArray;
        return  response;
    }
    QJsonObject jsonObject = jsonArray[0].toObject();
    user.read("email='"+jsonObject["email"].toString()+"'");

    //pastikan kalo di database ada satu user dengan email yang sama
    if(user.mUsers.size() != 1){
        QJsonArray errorArray,notificationArray;
        QJsonObject error,notification;
        error["error"] = "Email is not avaible or invalid";
        error["errorCode"] = "3";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
        response["error"] = errorArray;
        response["notification"] = notificationArray;
        return  response;
    }

    //pastikan username dan password benar
    QString password = jsonObject["password"].toString();
    QByteArray hashPass = QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Sha256);
    if(user.mUsers.at(0).password != QString::fromUtf8(hashPass.toHex())){
        QJsonArray errorArray,notificationArray;
        QJsonObject error,notification;
        error["error"] = "Wrong Password";
        error["errorCode"] = "3";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
        response["error"] = errorArray;
        response["notification"] = notificationArray;
        return  response;
    }
    QJsonWebToken jwt;

    //set secret
    jwt.setSecret(secret);

    // set a default payload
    jwt.appendClaim("iss", "WitchcraftHouse");
        //jwt.appendClaim("iat", QString::number(QDateTime::currentDateTime().toTime_t()));
    jwt.appendClaim("exp", QString::number(today.addMonths(1).toUTC().currentSecsSinceEpoch()));
    jwt.appendClaim("aud", jsonObject["email"].toString());
    jwt.appendClaim("jti", controlDeviceID.toString(QUuid::WithoutBraces));
        //jwt.appendClaim("sub", "hey there");

    QJsonObject loginToken;
    loginToken["email"] = jsonObject["email"].toString();
    loginToken["token"] = jwt.getToken();

    //buat control device
    QJsonObject createError = controlDevice.create(controlDeviceID,user.mUsers[0].userID,jsonObject["name"].toString(),jwt.getToken(),0,today.addMonths(1).toUTC().date());

    response["loginToken"] = loginToken;
    QJsonArray errorArray;
    errorArray.append(createError);
    response["error"] = errorArray;

    //send email notification
    QString title = "Token has been created";
    QString body = "Your token has been created. your token for "+jsonObject["name"].toString()+" is \n\n"+jwt.getToken()+"\n\nIf this is not you, you can disable this token from Witchcraft House application.\nplease do not reveal your password to anyone\nThank you";
    emit sendMail(jsonObject["email"].toString(),title,body);
    Log log(&db);
    log.create(user.mUsers.at(0).userID,"Created token for "+jsonObject["name"].toString()+".");

    return  response;
}

QJsonObject UserController::editUser(QJsonObject json, int userID)
{
    User user(&db);
    QJsonObject response;
    QJsonArray errorArray,notificationArray;
    QJsonObject jsonObject = json["editUser"].toObject();
    QJsonObject error = user.read("email='"+jsonObject["email"].toString()+"'");
    if((user.mUsers.size()!=1) || (user.mUsers.at(0).name == jsonObject["name"].toString())){
        QJsonObject error,notification;
        error["error"] = "you do not any info or name difference";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        QJsonObject error = user.update(userID,user.mUsers.at(0).email,user.mUsers.at(0).password,jsonObject["name"].toString());
        errorArray.append(error);
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject UserController::getUserInfo(int userID)
{
    User user(&db);
    QJsonObject response, jsonObject;
    QJsonArray errorArray,notificationArray;
    QJsonObject error = user.read("userID='"+QString::number(userID)+"'");
    errorArray.append(error);
    if(user.mUsers.size()!=1){
        QJsonObject error,notification;
        error["error"] = "no data to give";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        jsonObject["name"] = user.mUsers.at(0).name;
        jsonObject["email"] = user.mUsers.at(0).email;
    }
    response["userInfo"] = jsonObject;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject UserController::getControlDeviceList(int userID)
{
    ControllDevice control(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    QJsonObject error = control.read("userID='"+QString::number(userID)+"'");
    errorArray.append(error);
    if(control.mControlDevices.size()<1){
        QJsonObject error,notification;
        error["error"] = "no data to give";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<control.mControlDevices.size();i++) {
            QJsonObject jsonObject;
            //userID
            jsonObject["userName"] = control.mControlDevices.at(i).userName;
            jsonObject["expireDate"] = control.mControlDevices.at(i).expireDate.toString();
            jsonObject["controlDeviceID"] = control.mControlDevices.at(i).controlDeviceID.toString(QUuid::WithoutBraces);
            jsonObject["controlDeviceName"] = control.mControlDevices.at(i).controlDeviceName;
            //controlDeviceToken
            jsonObject["isControlDeviceOnline"] = control.mControlDevices.at(i).isControlDeviceOnline;
            jsonArray.append(jsonObject);
        }
    }
    response["controlDeviceList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject UserController::getAllDatalist(int userID)
{
    QJsonObject response;
    //inisialisasi controller
    DeviceController DC(&db);
    ScheduleController SC(&db);
    SharedController ShC(&db);

    //ambil tiap listnya
    QJsonObject pinList = DC.getPinList(userID);
    QJsonObject groupList = DC.getGroupList(userID);
    QJsonObject deviceList = DC.getDeviceList(userID);
    QJsonObject scheduleList = SC.getScheduleList(userID);
    QJsonObject sharedList = ShC.getSharedList(userID);
    QJsonObject sharedPin = ShC.getSharedPinList(userID);
    QJsonObject userInfo = getUserInfo(userID);
    QJsonObject controlDeviceList = getControlDeviceList(userID);

    //inisialisasi ke response
    response["pinList"] = pinList["pinList"].toArray();
    response["groupList"] = pinList["groupList"].toArray();
    response["deviceList"] = deviceList["deviceList"].toArray();
    response["scheduleList"] = scheduleList["scheduleList"].toArray();
    response["sharedList"] = sharedList["sharedList"].toArray();
    response["sharedPin"] = sharedPin["sharedPin"].toArray();
    response["userInfo"] = userInfo["userInfo"].toObject();
    response["controlDeviceList"] = controlDeviceList["controlDeviceList"].toArray();
    return response;
}
