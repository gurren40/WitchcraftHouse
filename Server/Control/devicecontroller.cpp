#include "devicecontroller.h"

DeviceController::DeviceController(QObject *parent) : QObject(parent)
{

}

DeviceController::DeviceController(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void DeviceController::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

void DeviceController::setSecret(QString secr)
{
    this->secret = secr;
}

bool DeviceController::isJwtValid(QJsonObject jwt, QString path)
{
    if(path == "/device"){
        if(jwt["iss"].toString() != "WitchcraftHouse") return false;
        User user(&db);
        user.read("email='"+jwt["aud"].toString()+"'");
        if(user.mUsers.size() != 1) return false;
        Device dd(&db);
        dd.read("deviceUUID=UuidToBin('"+jwt["jti"].toString()+"')");
        if(dd.mDevices.size() != 1) return  false;
        //QDateTime dt(dd.mDevices.at(0).expireDate);
        //if(dt.toSecsSinceEpoch() > jwt["exp"].toString().toInt()) return false;
        if(dd.mDevices.at(0).isDeviceOnline) return false;
        if(!toggleDeviceOnline(dd.mDevices.at(0).deviceUUID,true)) return false;
    }
    else {
        return false;
    }
    return  true;
}

bool DeviceController::toggleDeviceOnline(QUuid deviceUUID, bool toggle)
{
    Device devices(&db);
    devices.read("deviceUUID=UuidToBin('"+deviceUUID.toString(QUuid::WithoutBraces)+"')");
    if(devices.mDevices.size() != 1){
        return false;
    }
    if(devices.mDevices.at(0).isDeviceOnline == toggle){
        return false;
    }
    device dvc = devices.mDevices.at(0);
    devices.update(dvc.deviceID,dvc.deviceUUID,dvc.userID,dvc.deviceName,dvc.deviceToken,toggle,dvc.description);
    return true;
}

QJsonObject DeviceController::createNewDevice(QJsonObject json, int userID)
{
    Device device(&db);
    QJsonArray jsonArray = json["createNewDevice"].toArray();
    QJsonArray errorArray;
    QJsonArray notificationArray;

    if(jsonArray.size()>0){
        for (int i = 0;i < jsonArray.size();i++) {
            QJsonWebToken jwt;
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QUuid newUUID = QUuid::createUuid();
            jwt.setSecret(secret);
            //set jwt
            jwt.appendClaim("iss", "WitchcraftHouse");
            jwt.appendClaim("aud", jsonObject["email"].toString());
            jwt.appendClaim("jti", newUUID.toString(QUuid::WithoutBraces));

            //create new device
            QJsonObject error = device.create(newUUID,userID,jsonObject["deviceName"].toString(),jwt.getToken(),0,jsonObject["description"].toString());
            QJsonObject notification;
            notification["title"] = "Error";
            notification["description"] = error["error"].toString();
            //send email
            QString title = "Device token has been created";
            QString body = "Your new device token has been created.\nYour token is\n\n "+jwt.getToken()+" \n\nPlease use this token carefully, and If this is not you, you can disable this token from Witchcraft House application.\nplease do not reveal your password to anyone\nThank you";

            if(error["error"].toString() == "0"){
                emit sendMail(jsonObject["email"].toString(),title,body);
            }
            errorArray.append(error);
            notificationArray.append(notification);
        }
    }
    else {
        QJsonObject response;
        QJsonObject error,notification;
        error["error"] = "no information to create object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    QJsonObject response;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::createNewGroup(QJsonObject json, int userID)
{
    Group newGroup(&db);
    QJsonObject response;
    QJsonArray jsonArray;
    QJsonArray errorArray,notificationArray;
    jsonArray = json["createNewGroup"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to create object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QJsonObject error = newGroup.create(userID,json["iconID"].toInt(),json["groupName"].toString(),json["description"].toString());
            errorArray.append(error);
        }
    }
    response["notification"] = notificationArray;
    response["error"] = errorArray;
    return response;
}

QJsonObject DeviceController::createNewPin(QJsonObject json, int userID)
{
    Pin newPin(&db);
    QJsonObject response;
    QJsonArray jsonArray;
    QJsonArray errorArray;
    QJsonArray notificationArray;
    jsonArray = json["createNewPin"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to create object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QUuid newUUID = QUuid::createUuid();
            QJsonObject error = newPin.create(newUUID,userID,jsonObject["groupID"].toInt(),jsonObject["deviceID"].toInt(),jsonObject["iconID"].toInt(),jsonObject["pinTypeID"].toInt(),jsonObject["pinName"].toString(),jsonObject["value"].toString("0"),jsonObject["option"].toString(""),jsonObject["description"].toString(""));
            errorArray.append(error);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::editDevice(QJsonObject json, int userID)
{
    Device device(&db);
    QJsonObject response;
    QJsonArray jsonArray;
    QJsonArray errorArray,notificationArray;
    jsonArray = json["editDevice"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to create object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QJsonObject error = device.read("deviceID='"+QString::number(jsonObject["deviceID"].toInt())+"'");
            if(device.mDevices.size()==1){
                error = device.update(jsonObject["deviceID"].toInt(),QUuid::fromString(jsonObject["deviceUUID"].toString()),userID,jsonObject["deviceName"].toString(),device.mDevices.at(0).deviceToken,device.mDevices.at(0).isDeviceOnline,jsonObject["description"].toString());
                errorArray.append(error);
            }
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::editGroup(QJsonObject json, int userID)
{
    Group group(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["editGroup"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to create object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QJsonObject error = group.read("groupID='"+QString::number(jsonObject["groupID"].toInt())+"'");
            if(group.mGroups.size() == 1){
                error = group.update(jsonObject["groupID"].toInt(),userID,jsonObject["iconID"].toInt(),jsonObject["groupName"].toString(),jsonObject["description"].toString());
            }
            errorArray.append(error);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::editPin(QJsonObject json, int userID)
{
    Pin pin(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["editPin"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to create object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QUuid UUID = QUuid::fromString(jsonObject["UUID"].toString());
            QJsonObject error = pin.read("UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"'");
            if(pin.mPins.size() == 1){
                error = pin.update(pin.mPins.at(0).pinID,pin.mPins.at(0).UUID,userID,jsonObject["groupID"].toInt(),jsonObject["deviceID"].toInt(),jsonObject["iconID"].toInt(),jsonObject["pinTypeID"].toInt(),jsonObject["pinName"].toString(),pin.mPins.at(0).value,jsonObject["option"].toString(),jsonObject["description"].toString());
            }
            errorArray.append(error);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}
