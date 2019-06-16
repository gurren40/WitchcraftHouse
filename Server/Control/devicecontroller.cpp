#include "devicecontroller.h"

DeviceController::DeviceController(QObject *parent) : QObject(parent)
{

}

DeviceController::DeviceController(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

int DeviceController::getUserIDByDeviceID(QUuid deviceUUID)
{
    Device device(&db);
    device.read("Device.deviceUUID=UuidToBin('"+deviceUUID.toString(QUuid::WithoutBraces)+"')");
    if(device.mDevices.size()!=1){
        return 0;
    }
    else {
        return device.mDevices.at(0).userID;
    }
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
        QTextStream(stdout) << "start" << "\n";
        if(jwt["iss"].toString() != "WitchcraftHouse") return false;
        QTextStream(stdout) << "iss validation" << "\n";
        User user(&db);
        user.read("email='"+jwt["aud"].toString()+"'");
        if(user.mUsers.size() != 1) return false;
        QTextStream(stdout) << "if user size != 1" << "\n";
        Device dd(&db);
        dd.read("Device.deviceUUID=UuidToBin('"+jwt["jti"].toString()+"')");
        if(dd.mDevices.size() != 1) return  false;
        QTextStream(stdout) << "if device size != 1" << "\n";
        //QDateTime dt(dd.mDevices.at(0).expireDate);
        //if(dt.toSecsSinceEpoch() > jwt["exp"].toString().toInt()) return false;
        if(dd.mDevices.at(0).isDeviceOnline) {
            toggleDeviceOnline(dd.mDevices.at(0).deviceUUID,false);
            emit disconnectDevice(jwt["jti"].toString());
            return false;
        }
        QTextStream(stdout) << "is device online" << "\n";
        if(!toggleDeviceOnline(dd.mDevices.at(0).deviceUUID,true)) return false;
        QTextStream(stdout) << "toogle device" << "\n";
    }
    else {
        return false;
    }
    return  true;
}

bool DeviceController::toggleDeviceOnline(QUuid deviceUUID, bool toggle)
{
    Device devices(&db);
    devices.read("Device.deviceUUID=UuidToBin('"+deviceUUID.toString(QUuid::WithoutBraces)+"')");
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

            User user(&db);
            user.read("userID='"+QString::number(userID)+"'");
            if(user.mUsers.size()!=1){
                QTextStream(stdout) << userID << "\n";
                QJsonObject error,notification;
                error["error"] = "userID invalid";
                error["errorCode"] = "7";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
                errorArray.append(error);
                notificationArray.append(notification);
            }
            else {
                jsonObject["email"] = user.mUsers.at(0).email;
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
                    Log log(&db);
                    log.create(userID,"Device "+jsonObject["deviceName"].toString()+" has been created");
                }
                errorArray.append(error);
                notificationArray.append(notification);
            }
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
            QJsonObject error = newGroup.create(userID,jsonObject["iconID"].toInt(),jsonObject["groupName"].toString(),jsonObject["description"].toString());
            errorArray.append(error);
            Log log(&db);
            log.create(userID,"Group "+jsonObject["groupName"].toString()+" has been created");
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
            Log log(&db);
            log.create(userID,"Pin "+jsonObject["pinName"].toString()+" has been created");
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
        error["error"] = "no information to edit object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QJsonObject error = device.read("Device.deviceID='"+QString::number(jsonObject["deviceID"].toInt())+"'");
            if(device.mDevices.size()==1){
                error = device.update(jsonObject["deviceID"].toInt(),QUuid::fromString(jsonObject["deviceUUID"].toString()),userID,jsonObject["deviceName"].toString(),device.mDevices.at(0).deviceToken,device.mDevices.at(0).isDeviceOnline,jsonObject["description"].toString());
                errorArray.append(error);
                Log log(&db);
                log.create(userID,"Device "+jsonObject["deviceName"].toString()+" has been edited");
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
        error["error"] = "no information to edit object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QJsonObject error = group.read("Groups.groupID='"+QString::number(jsonObject["groupID"].toInt())+"'");
            if(group.mGroups.size() == 1){
                error = group.update(jsonObject["groupID"].toInt(),userID,jsonObject["iconID"].toInt(),jsonObject["groupName"].toString(),jsonObject["description"].toString());
                Log log(&db);
                log.create(userID,"Group "+jsonObject["groupName"].toString()+" has been edited");
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
        error["error"] = "no information to edit object";
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
            QJsonObject error = pin.read("Pin.UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"')");
            if(pin.mPins.size() == 1){
                //error = pin.update(pin.mPins.at(0).pinID,pin.mPins.at(0).UUID,userID,jsonObject["groupID"].toInt(),jsonObject["deviceID"].toInt(),jsonObject["iconID"].toInt(),jsonObject["pinTypeID"].toInt(),jsonObject["pinName"].toString(),pin.mPins.at(0).value,jsonObject["option"].toString(),jsonObject["description"].toString());
                error = pin.update(pin.mPins.at(0).pinID,pin.mPins.at(0).UUID,userID,jsonObject["groupID"].toInt(),jsonObject["deviceID"].toInt(),jsonObject["iconID"].toInt(),jsonObject["pinTypeID"].toInt(),jsonObject["pinName"].toString(),jsonObject["value"].toString(),jsonObject["option"].toString(),jsonObject["description"].toString());
                Log log(&db);
                log.create(userID,"Pin "+jsonObject["pinName"].toString()+" has been edited");
            }
            errorArray.append(error);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::deleteDevice(QJsonObject json, int userID)
{
    Device device(&db);
    Pin pin(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["deleteDevice"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to delete object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QJsonObject error1 = device.read("Device.deviceID='"+QString::number(jsonObject["deviceID"].toInt())+"'");
            if(device.mDevices.size() == 1){

                //delete pin
                pin.read("Pin.deviceID='"+QString::number(device.mDevices.at(0).deviceID)+"'");
                if(pin.mPins.size()>0){
                    QJsonArray pinArray;
                    for (int j = 0;j<pin.mPins.size();j++) {
                        QJsonObject pinObject;
                        pinObject["UUID"]=pin.mPins.at(j).UUID.toString(QUuid::WithoutBraces);
                        pinArray.append(pinObject);
                    }
                    QJsonObject pinList;
                    pinList["deletePin"] = pinArray;
                    QJsonObject error2 = deletePin(pinList,userID);
                    errorArray.append(error2);
                }

                //delete device
                //[ERROR]
                emit deletedDevice(device.mDevices.at(i).deviceUUID);
                //[ERROR]
                error1 = device.deletes("deviceID='"+QString::number(device.mDevices.at(0).deviceID)+"'");
                Log log(&db);
                log.create(userID,"Device "+device.mDevices.at(0).deviceName+" has been deleted");
            }
            errorArray.append(error1);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::deleteGroup(QJsonObject json, int userID)
{
    Group group(&db);
    Pin pin(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["deleteGroup"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to delete object";
        error["errorCode"] = "6";
        notification["title"]="error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            QJsonObject error1 = group.read("Groups.groupID='"+QString::number(jsonObject["groupID"].toInt())+"'");
            if(group.mGroups.size() == 1){

                //delete pin
                pin.read("Pin.groupID='"+QString::number(group.mGroups.at(0).groupID)+"'");
                if(pin.mPins.size()>0){
                    QJsonArray pinArray;
                    for (int j = 0;j<pin.mPins.size();j++) {
                        QJsonObject pinObject;
                        pinObject["UUID"]=pin.mPins.at(j).UUID.toString(QUuid::WithoutBraces);
                        pinArray.append(pinObject);
                    }
                    QJsonObject pinList;
                    pinList["deletePin"] = pinArray;
                    QJsonObject error2 = deletePin(pinList,userID);
                    errorArray.append(error2);
                }

                //delete group
                emit deletedGroup(jsonObject["groupID"].toInt(),userID);
                error1 = group.deletes("groupID='"+QString::number(group.mGroups.at(0).groupID)+"'");
                Log log(&db);
                log.create(userID,"Group "+group.mGroups.at(0).groupName+" has been deleted");
            }
            errorArray.append(error1);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::deletePin(QJsonObject json, int userID)
{
    Pin pin(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["deletePin"].toArray();
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "no information to delete object";
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
            QJsonObject error = pin.read("Pin.UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"')");
            if(pin.mPins.size() == 1){
                error = pin.deletes("UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"')");
                emit deletedPin(UUID,userID);
                Log log(&db);
                log.create(userID,"Pin "+pin.mPins.at(0).pinName+" has been deleted");
            }
            errorArray.append(error);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::getDeviceList(int userID)
{
    Device device(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    QJsonObject error = device.read("User.userID='"+QString::number(userID)+"'");

    if(device.mDevices.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any device. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<device.mDevices.size();i++) {
            QJsonObject deviceObject;
            deviceObject["deviceID"] = device.mDevices.at(i).deviceID;
            deviceObject["userName"] = device.mDevices.at(i).userName;
            deviceObject["deviceUUID"] = device.mDevices.at(i).deviceUUID.toString(QUuid::WithoutBraces);
            deviceObject["deviceName"] = device.mDevices.at(i).deviceName;
            deviceObject["isDeviceOnline"] = device.mDevices.at(i).isDeviceOnline;
            deviceObject["deviceToken"] = device.mDevices.at(i).deviceToken;
            deviceObject["description"] = device.mDevices.at(i).description;
            jsonArray.append(deviceObject);
        }
    }
    response["deviceList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::getGroupList(int userID)
{
    Group group(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    QJsonObject error = group.read("User.userID='"+QString::number(userID)+"'");

    if(group.mGroups.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any group. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<group.mGroups.size();i++) {
            QJsonObject groupObject;
            groupObject["groupID"] = group.mGroups.at(i).groupID;
            //groupObject["userID"] = group.mGroups.at(i).userID;
            groupObject["iconID"] = group.mGroups.at(i).iconID;
            groupObject["groupName"] = group.mGroups.at(i).groupName;
            groupObject["userName"] = group.mGroups.at(i).userName;
            groupObject["iconName"] = group.mGroups.at(i).iconName;
            groupObject["description"] = group.mGroups.at(i).description;
            jsonArray.append(groupObject);
        }
    }
    response["groupList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::getPinList(int userID)
{
    Pin pin(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    QJsonObject error = pin.read("Pin.userID='"+QString::number(userID)+"'");

    if(pin.mPins.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any Pin. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<pin.mPins.size();i++) {
            QJsonObject pinObject;
            pinObject["pinID"] = pin.mPins.at(i).pinID;
            pinObject["UUID"] = pin.mPins.at(i).UUID.toString(QUuid::WithoutBraces);
            //groupObject["userID"] = pin.mPins.at(i).userID;
            pinObject["userName"] = pin.mPins.at(i).userName;
            pinObject["groupID"] = pin.mPins.at(i).groupID;
            pinObject["groupName"] = pin.mPins.at(i).groupName;
            pinObject["deviceID"] = pin.mPins.at(i).deviceID;
            pinObject["deviceName"] = pin.mPins.at(i).deviceName;
            pinObject["iconID"] = pin.mPins.at(i).iconID;
            pinObject["iconName"] = pin.mPins.at(i).iconName;
            pinObject["pinTypeID"] = pin.mPins.at(i).pinTypeID;
            pinObject["pinTypeName"] = pin.mPins.at(i).pinTypeName;
            pinObject["pinName"] = pin.mPins.at(i).pinName;
            pinObject["value"] = pin.mPins.at(i).value;
            pinObject["option"] = pin.mPins.at(i).option;
            pinObject["description"] = pin.mPins.at(i).description;
            jsonArray.append(pinObject);
        }
    }
    response["pinList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::setPinValue(QJsonObject json, int userID)
{
    QJsonObject response;
    QJsonArray errorArray,notificationArray;
    QJsonArray jsonArray = json["setPinValue"].toArray();
    QHash<QUuid,QJsonArray> sortedPinToDevice;
    Device device(&db);
    Pin pin(&db);
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "there is no pin to set";
        error["errorCode"] = "8";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject pinObject = jsonArray.at(i).toObject();
            QUuid UUID = QUuid::fromString(pinObject["UUID"].toString());
            QJsonObject error2;
            QJsonObject error1 = pin.read("Pin.UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"')");

            //check kalau pin ada, lalu dapatkan device id
            if(pin.mPins.size()==1){
                error2 = device.read("Device.deviceID='"+QString::number(pin.mPins.at(0).deviceID)+"'");
                //check kalau device ada, lalu dapatkan UUIDnya
                if(device.mDevices.size()==1){
                    if (sortedPinToDevice.isEmpty()){
                        //kalau belum di hash
                        QJsonArray toHashArray;
                        toHashArray.append(pinObject);
                        sortedPinToDevice.insert(device.mDevices.at(0).deviceUUID,toHashArray);
                    }
                    else if (sortedPinToDevice.contains(device.mDevices.at(0).deviceUUID)){
                        //kalau sudah di hash
                        QJsonArray toHashArray = sortedPinToDevice.value(device.mDevices.at(0).deviceUUID);
                        toHashArray.append(pinObject);
                        sortedPinToDevice.remove(device.mDevices.at(0).deviceUUID);
                        sortedPinToDevice.insert(device.mDevices.at(0).deviceUUID,toHashArray);
                    }
                    else {
                        //kalau belum di hash
                        QJsonArray toHashArray;
                        toHashArray.append(pinObject);
                        sortedPinToDevice.insert(device.mDevices.at(0).deviceUUID,toHashArray);
                    }
                }
            }
            errorArray.append(error1);
            errorArray.append(error2);
        }
//        QHash<QUuid,QJsonArray>::iterator j;
//        for (j = sortedPinToDevice.begin(); j != sortedPinToDevice.end(); ++j){
//            QJsonObject toSend;
//            toSend["setPinValue"] = j.value();
//            emit broadcastToDevice(j.key(),toSend);
//        }
        QList<QUuid> theKeys;
        theKeys = sortedPinToDevice.keys();
        for (int j = 0; j < theKeys.size();j++) {
            QTextStream(stdout) << theKeys.at(j).toString() << "\n";
            QJsonArray theArray;
            QUuid theKey =theKeys.value(j);
            theArray = sortedPinToDevice.value(theKey);
            QJsonObject toSend;
            toSend["setPinValue"] = theArray;
            emit broadcastToDevice(theKey,toSend);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject DeviceController::settedPinValue(QJsonObject json, int userID)
{
    QJsonObject response;
    QJsonArray errorArray,notificationArray;
    QJsonArray jsonArray = json["settedPinValue"].toArray();
    QHash<int,QJsonArray> sortedPinByUser;
    //Device device(&db);
    Pin pin(&db);
    PinLog pinLog(&db);
    if(jsonArray.size()<1){
        QJsonObject error,notification;
        error["error"] = "there is no pin to set";
        error["errorCode"] = "8";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject pinObject = jsonArray.at(i).toObject();
            QUuid UUID = QUuid::fromString(pinObject["UUID"].toString());
            QJsonObject error1 = pin.read("Pin.UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"')");
            //check kalau pin ada, lalu dapatkan device id
            if(pin.mPins.size()==1){
                if(sortedPinByUser.isEmpty()){
                    QJsonArray toHashArray;// = sortedPinToDevice.value(device.mDevices.at(0).deviceUUID);
                    toHashArray.append(pinObject);
                    //sortedPinToDevice.remove(device.mDevices.at(0).deviceUUID);
                    sortedPinByUser.insert(pin.mPins.at(0).userID,toHashArray);
                }
                else if (sortedPinByUser.contains(pin.mPins.at(0).userID)){
                    QJsonArray toHashArray = sortedPinByUser.value(pin.mPins.at(0).userID);
                    toHashArray.append(pinObject);
                    sortedPinByUser.remove(pin.mPins.at(0).userID);
                    sortedPinByUser.insert(pin.mPins.at(0).userID,toHashArray);
                }
                //kalau belum di hash
                else {
                    QJsonArray toHashArray;// = sortedPinToDevice.value(device.mDevices.at(0).deviceUUID);
                    toHashArray.append(pinObject);
                    //sortedPinToDevice.remove(device.mDevices.at(0).deviceUUID);
                    sortedPinByUser.insert(pin.mPins.at(0).userID,toHashArray);
                }
                QJsonObject error2 = pin.update(pin.mPins.at(0).pinID,pin.mPins.at(0).UUID,pin.mPins.at(0).userID,pin.mPins.at(0).groupID,pin.mPins.at(0).deviceID,pin.mPins.at(0).iconID,pin.mPins.at(0).pinTypeID,pin.mPins.at(0).pinName,pinObject["value"].toString(),pin.mPins.at(0).option,pin.mPins.at(0).description);
                pinLog.create(userID,pin.mPins.at(0).pinID,pinObject["value"].toString(),"pin "+pin.mPins.at(0).pinName+" value is changed to "+pinObject["value"].toString()+" at "+QDateTime::currentDateTime().toString());
                emit broadcastToShared(UUID,userID);
                errorArray.append(error1);
                errorArray.append(error2);
            }
        }
//        QHash<int,QJsonArray>::iterator j;
//        for (j = sortedPinByUser.begin(); j != sortedPinByUser.end(); ++j){
//            QJsonObject toSend;
//            toSend["settedPinValue"] = j.value();
//            emit broadcastToAllUserControlDevice(j.key(),toSend);
//        }
        QList<int> theKeys;
        theKeys = sortedPinByUser.keys();
        for (int j = 0; j < theKeys.size();j++) {
            QJsonArray theArray;
            int theKey =theKeys.value(j);
            theArray = sortedPinByUser.value(theKey);
            QJsonObject toSend;
            toSend["settedPinValue"] = theArray;
            emit broadcastToAllUserControlDevice(theKey,toSend);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}
