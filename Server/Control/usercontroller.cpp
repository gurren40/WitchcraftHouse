#include "usercontroller.h"

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
    return  response;
}
