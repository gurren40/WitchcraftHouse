#include "logcontroller.h"

LogController::LogController(QObject *parent) : QObject(parent)
{

}

LogController::LogController(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    db = *database;
}

void LogController::setSecret(const QString &value)
{
    secret = value;
}

void LogController::setDatabase(const QSqlDatabase &value)
{
    db = value;
}

QJsonObject LogController::getAllLog(int userID)
{
    QJsonObject pinLog = getAllPinLog(userID);
    QJsonObject log = getAllActivityLog(userID);
    QJsonObject response;
    response["pinLogList"] = pinLog["pinLogList"].toObject();
    response["activityLogList"] = log["activityLogList"].toObject();
    return response;
}

QJsonObject LogController::getAllPinLog(int userID)
{
    PinLog pinLog(&db);
    Pin pin(&db);
    QJsonObject response,jsonObj;
    QJsonArray errorArray,notificationArray,jsonKeys;
    pin.read("Pin.userID = '"+QString::number(userID)+"'");
    if(pin.mPins.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any pin. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else{
        for (int i = 0;i<pin.mPins.size();i++) {
            QJsonArray pinLogArr;
            //QJsonObject key;
            pinLog.read("PinLog.pinID = '"+QString::number(pin.mPins.at(i).pinID)+"'");
            if(pinLog.mPinLog.size()<1){
                QJsonObject error,notification;
                error["error"] = "no pinlog for this pin";
                error["errorCode"] = "7";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
                errorArray.append(error);
                notificationArray.append(notification);
            }
            else {
                for (int j = 0;j<pinLog.mPinLog.size();j++) {
                    QJsonObject logOBj;
                    logOBj["pinLogID"] = pinLog.mPinLog.at(j).pinLogID;
                    logOBj["userID"] = pinLog.mPinLog.at(j).userID;
                    logOBj["userName"] = pinLog.mPinLog.at(j).userName;
                    logOBj["pinID"] = pinLog.mPinLog.at(j).pinID;
                    logOBj["pinName"] = pinLog.mPinLog.at(j).pinName;
                    logOBj["pinUUID"] = pinLog.mPinLog.at(j).pinUUID.toString();
                    logOBj["pinTypeID"] = pinLog.mPinLog.at(j).pinTypeID;
                    logOBj["pinTypeName"] = pinLog.mPinLog.at(j).pinTypeName;
                    logOBj["value"] = pinLog.mPinLog.at(j).value;
                    logOBj["description"] = pinLog.mPinLog.at(j).description;
                    logOBj["timeStamp"] = pinLog.mPinLog.at(j).timeStamp.toString();
                    pinLogArr.append(logOBj);
                }
            }
            //key["UUID"] = pin.mPins.at(i).UUID.toString(QUuid::WithoutBraces);
            jsonObj[pin.mPins.at(i).UUID.toString(QUuid::WithoutBraces)] = pinLogArr;
            jsonKeys.append(pin.mPins.at(i).UUID.toString(QUuid::WithoutBraces));
        }
    }
    jsonObj["keys"] = jsonKeys;
    response["pinLogList"] = jsonObj;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject LogController::getAllActivityLog(int userID)
{
    Log log(&db);
    QJsonObject response;
    QJsonArray errorArray,notificationArray,jsonArray;
    log.read("Log.userID='"+QString::number(userID)+"'");
    if(log.mLogs.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any activity log.";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<log.mLogs.size();i++) {
            QJsonObject jsonObject;
            jsonObject["logID"] = log.mLogs.at(i).logID;
            jsonObject["userID"] = log.mLogs.at(i).userID;
            jsonObject["userName"] = log.mLogs.at(i).userName;
            jsonObject["description"] = log.mLogs.at(i).description;
            jsonObject["timeStamp"] = log.mLogs.at(i).timeStamp.toString();
            jsonArray.append(jsonObject);
        }
    }
    response["activityLogList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject LogController::getPinLog(int userID, int pinID)
{
    PinLog pinLog(&db);
    Pin pin(&db);
    QJsonObject response,jsonObj;
    QJsonArray errorArray,notificationArray,jsonKeys;
    pin.read("Pin.pinID = '"+QString::number(pinID)+"'");
    if((pin.mPins.size()<1) || (userID != pin.mPins.at(0).userID)){
        QJsonObject error,notification;
        error["error"] = "you do not have any pin. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else{
        for (int i = 0;i<pin.mPins.size();i++) {
            QJsonArray pinLogArr;
            QJsonObject key;
            pinLog.read("PinLog.pinID = '"+QString::number(pin.mPins.at(i).pinID)+"'");
            if(pinLog.mPinLog.size()<1){
                QJsonObject error,notification;
                error["error"] = "no pinlog for this pin";
                error["errorCode"] = "7";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
                errorArray.append(error);
                notificationArray.append(notification);
            }
            else {
                for (int j = 0;j<pinLog.mPinLog.size();j++) {
                    QJsonObject logOBj;
                    logOBj["pinLogID"] = pinLog.mPinLog.at(j).pinLogID;
                    logOBj["userID"] = pinLog.mPinLog.at(j).userID;
                    logOBj["userName"] = pinLog.mPinLog.at(j).userName;
                    logOBj["pinID"] = pinLog.mPinLog.at(j).pinID;
                    logOBj["pinName"] = pinLog.mPinLog.at(j).pinName;
                    logOBj["pinUUID"] = pinLog.mPinLog.at(j).pinUUID.toString();
                    logOBj["pinTypeID"] = pinLog.mPinLog.at(j).pinTypeID;
                    logOBj["pinTypeName"] = pinLog.mPinLog.at(j).pinTypeName;
                    logOBj["value"] = pinLog.mPinLog.at(j).value;
                    logOBj["description"] = pinLog.mPinLog.at(j).description;
                    logOBj["timeStamp"] = pinLog.mPinLog.at(j).timeStamp.toString();
                    pinLogArr.append(logOBj);
                }
            }
            key["UUID"] = pin.mPins.at(i).UUID.toString(QUuid::WithoutBraces);
            jsonObj[pin.mPins.at(i).UUID.toString(QUuid::WithoutBraces)] = pinLogArr;
            jsonKeys.append(key);
        }
    }
    jsonObj["keys"] = jsonKeys;
    response["pinLogList"] = jsonObj;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject LogController::deleteAllLog(int userID)
{
    QJsonArray errorArray;
    QJsonObject response;
    QJsonObject response1 = deleteAllPinLog(userID);
    QJsonObject response2 = deleteAllActivityLog(userID);
    for (int i = 0;i<response1["error"].toArray().size();i++) {
        QJsonObject error = response1["error"].toArray().at(i).toObject();
        errorArray.append(error);
    }
    for (int i = 0;i<response2["error"].toArray().size();i++) {
        QJsonObject error = response2["error"].toArray().at(i).toObject();
        errorArray.append(error);
    }
    response["error"] = errorArray;
    return response;
}

QJsonObject LogController::deleteAllPinLog(int userID)
{
    PinLog pinLog(&db);
    QJsonObject response = pinLog.deletes("userID='"+QString::number(userID)+"'");
    return response;
}

QJsonObject LogController::deleteAllActivityLog(int userID)
{
    Log log(&db);
    QJsonObject response = log.deletes("userID='"+QString::number(userID)+"'");
    return response;
}
