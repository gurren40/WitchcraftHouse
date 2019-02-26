#include "sharedcontroller.h"
#include "Entity/user.h"
#include "Entity/pin.h"

SharedController::SharedController(QObject *parent) : QObject(parent)
{

}

SharedController::SharedController(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void SharedController::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject SharedController::createNewShared(QJsonObject json, int userID)
{
    Shared shared(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["createNewShared"].toArray();
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
            QJsonObject error;
            QJsonObject notification;
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            int sharedBy = userID;
            int sharedTo = getSharedToID(jsonObject["sharedTo"].toString());
            if (sharedTo > 0){
                bool sharedType = jsonObject["sharedType"].toBool();
                int groupID = jsonObject["groupID"].toInt(0);
                QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
                int pinID = getPinIDbyUUID(UUID);
                if(pinID > 0){
                    QString sharedName = jsonObject["sharedName"].toString();
                    QString description = jsonObject["description"].toString(" ");
                    error = shared.create(sharedBy,sharedTo,sharedType,groupID,pinID,sharedName,description);
                }
                else {
                    error["error"] = "pin "+json["pinUUID"].toString()+" is not valid";
                    error["errorCode"] = "9";
                    notification["title"]="Error";
                    notification["description"] = error["error"].toString();
                }
            }
            else {
                error["error"] = "email "+json["sharedTo"].toString()+" is not valid";
                error["errorCode"] = "9";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
            }
            errorArray.append(error);
            notificationArray.append(notificationArray);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject SharedController::editShared(QJsonObject json, int userID)
{
    Shared shared(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["editShared"].toArray();
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
            QJsonObject error;
            QJsonObject notification;
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            int sharedID = jsonObject["sharedID"].toInt();
            shared.read("sharedID='"+QString::number(sharedID)+"'");
            if(shared.mShareds.size() != 1){
                error["error"] = "sharedID "+json["sharedID"].toString()+" is not valid";
                error["errorCode"] = "9";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
            }
            else {
                int sharedBy = userID;
                int sharedTo = getSharedToID(jsonObject["sharedTo"].toString());
                if (sharedTo > 0){
                    bool sharedType = jsonObject["sharedType"].toBool();
                    int groupID = jsonObject["groupID"].toInt(0);
                    QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
                    int pinID = getPinIDbyUUID(UUID);
                    if(pinID > 0){
                        QString sharedName = jsonObject["sharedName"].toString();
                        QString description = jsonObject["description"].toString(" ");
                        error = shared.update(sharedID,sharedBy,sharedTo,sharedType,groupID,pinID,sharedName,description);
                    }
                    else {
                        error["error"] = "pin "+json["pinUUID"].toString()+" is not valid";
                        error["errorCode"] = "9";
                        notification["title"]="Error";
                        notification["description"] = error["error"].toString();
                    }
                }
                else {
                    error["error"] = "email "+json["sharedTo"].toString()+" is not valid";
                    error["errorCode"] = "9";
                    notification["title"]="Error";
                    notification["description"] = error["error"].toString();
                }
            }
            errorArray.append(error);
            notificationArray.append(notificationArray);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject SharedController::deleteShared(QJsonObject json, int userID)
{
    Shared shared(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["deleteShared"].toArray();
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
            QJsonObject error;
            QJsonObject notification;
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            int sharedID = jsonObject["sharedID"].toInt();
            shared.read("sharedID='"+QString::number(sharedID)+"'");
            if((shared.mShareds.size() != 1) && (shared.mShareds.at(0).sharedBy != userID)){
                error["error"] = "sharedID "+json["sharedID"].toString()+" is not valid";
                error["errorCode"] = "9";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
            }
            else {
                error = shared.deletes("sharedID='"+QString::number(sharedID)+"'");
            }
            errorArray.append(error);
            notificationArray.append(notificationArray);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject SharedController::getSharedList(int userID)
{
    Shared shared(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    QJsonObject error = shared.read("userID='"+QString::number(userID)+"'");
    errorArray.append(error);
    if(shared.mShareds.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any shared item. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<shared.mShareds.size();i++) {
            QJsonObject jsonObject;
            jsonObject["sharedID"] = shared.mShareds.at(i).sharedID;
            jsonObject["sharedTo"] = getSharedToEmail(shared.mShareds.at(i).sharedTo);
            jsonObject["sharedToName"] = shared.mShareds.at(i).sharedToName;
            jsonObject["sharedType"] = shared.mShareds.at(i).sharedType;
            jsonObject["groupID"] = shared.mShareds.at(i).groupID;
            jsonObject["groupName"] = shared.mShareds.at(i).groupName;
            jsonObject["pinUUID"] = shared.mShareds.at(i).pinUUID.toString(QUuid::WithoutBraces);
            jsonObject["pinName"] = shared.mShareds.at(i).pinName;
            jsonObject["sharedName"] = shared.mShareds.at(i).sharedName;
            jsonObject["description"] = shared.mShareds.at(i).description;
            jsonArray.append(jsonObject);
        }
    }
    response["sharedList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject SharedController::getSharedPinList(int userID)
{
    Pin pin(&db);
    Shared shared(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;

    QJsonObject error1 = shared.read("sharedTo='"+QString::number(userID)+"'");
    if(shared.mShareds.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any shared pin. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<shared.mShareds.size();i++) {
            //kalau yang di share adalah pin
            if(shared.mShareds.at(i).sharedType){
                QJsonObject error = pin.read("Pin.pinID='"+QString::number(shared.mShareds.at(i).pinID)+"'");
                if(pin.mPins.size()!=1){
                    QJsonObject error,notification;
                    error["error"] = "you do not have this shared Pin. please create one";
                    error["errorCode"] = "7";
                    notification["title"]="Error";
                    notification["description"] = error["error"].toString();
                    errorArray.append(error);
                    notificationArray.append(notification);
                }
                else {
                    for (int j = 0;j<pin.mPins.size();j++) {
                        QJsonObject pinObject;
                        pinObject["pinID"] = pin.mPins.at(j).pinID;
                        pinObject["UUID"] = pin.mPins.at(j).UUID.toString(QUuid::WithoutBraces);
                        //groupObject["userID"] = pin.mPins.at(j).userID;
                        pinObject["userName"] = pin.mPins.at(j).userName;
                        pinObject["groupID"] = pin.mPins.at(j).groupID;
                        pinObject["groupName"] = pin.mPins.at(j).groupName;
                        pinObject["deviceID"] = pin.mPins.at(j).deviceID;
                        pinObject["deviceName"] = pin.mPins.at(j).deviceName;
                        pinObject["iconID"] = pin.mPins.at(j).iconID;
                        pinObject["iconName"] = pin.mPins.at(j).iconName;
                        pinObject["pinTypeID"] = pin.mPins.at(j).pinTypeID;
                        pinObject["pinTypeName"] = pin.mPins.at(j).pinTypeName;
                        pinObject["value"] = pin.mPins.at(j).value;
                        pinObject["option"] = pin.mPins.at(j).option;
                        pinObject["description"] = pin.mPins.at(j).description;
                        jsonArray.append(pinObject);
                        errorArray.append(error);
                    }
                }
            }

            //kalau yang di share adalah group
            else {
                QJsonObject error = pin.read("Pin.groupID='"+QString::number(shared.mShareds.at(i).groupID)+"'");
                if(pin.mPins.size()<1){
                    QJsonObject error,notification;
                    error["error"] = "you do not have this shared Group. please create one";
                    error["errorCode"] = "7";
                    notification["title"]="Error";
                    notification["description"] = error["error"].toString();
                    errorArray.append(error);
                    notificationArray.append(notification);
                }
                else {
                    for (int j = 0;j<pin.mPins.size();j++) {
                        QJsonObject pinObject;
                        pinObject["pinID"] = pin.mPins.at(j).pinID;
                        pinObject["UUID"] = pin.mPins.at(j).UUID.toString(QUuid::WithoutBraces);
                        //groupObject["userID"] = pin.mPins.at(j).userID;
                        pinObject["userName"] = pin.mPins.at(j).userName;
                        pinObject["groupID"] = pin.mPins.at(j).groupID;
                        pinObject["groupName"] = pin.mPins.at(j).groupName;
                        pinObject["deviceID"] = pin.mPins.at(j).deviceID;
                        pinObject["deviceName"] = pin.mPins.at(j).deviceName;
                        pinObject["iconID"] = pin.mPins.at(j).iconID;
                        pinObject["iconName"] = pin.mPins.at(j).iconName;
                        pinObject["pinTypeID"] = pin.mPins.at(j).pinTypeID;
                        pinObject["pinTypeName"] = pin.mPins.at(j).pinTypeName;
                        pinObject["value"] = pin.mPins.at(j).value;
                        pinObject["option"] = pin.mPins.at(j).option;
                        pinObject["description"] = pin.mPins.at(j).description;
                        jsonArray.append(pinObject);
                        errorArray.append(error);
                    }
                }
            }
        }
    }
    response["sharedPinList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

int SharedController::getSharedToID(QString email)
{
    User user(&db);
    user.read("email='"+email+"'");
    if(user.mUsers.size()!=1){
        return 0;
    }
    else return user.mUsers.at(0).userID;
}

QString SharedController::getSharedToEmail(int sharedToID)
{
    User user(&db);
    user.read("userID='"+QString::number(sharedToID)+"'");
    if(user.mUsers.size()!=1){
        return  "invalid";
    }
    else return  user.mUsers.at(0).email;
}

int SharedController::getPinIDbyUUID(QUuid UUID)
{
    Pin pin(&db);
    pin.read("UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"'");
    if(pin.mPins.size()!=1){
        return 0;
    }
    else return  pin.mPins.at(0).pinID;
}
