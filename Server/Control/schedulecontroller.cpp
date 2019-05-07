#include "schedulecontroller.h"

#include "Entity/pin.h"
#include "Entity/log.h"

ScheduleController::ScheduleController(QObject *parent) : QObject(parent)
{

}

ScheduleController::ScheduleController(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void ScheduleController::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject ScheduleController::createNewSchedule(QJsonObject json, int userID)
{
    Schedule newSchedule(&db);
    QJsonObject response;
    QJsonArray errorArray,notificationArray;
    QJsonArray jsonArray = json["createNewSchedule"].toArray();
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
            QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
            QUuid scheduleUUID = QUuid::createUuid();
            int pinID = getPinIDbyUUID(UUID);
            QString scheduleName = jsonObject["scheduleName"].toString();
            QString minute = jsonObject["minute"].toString();
            QString hour = jsonObject["hour"].toString();
            QString dayOfMonth = jsonObject["dayOfMonth"].toString();
            QString month = jsonObject["month"].toString();
            QString dayOfWeek = jsonObject["dayOfWeek"].toString();
            QString timeZone = jsonObject["timeZone"].toString();
            QString value = jsonObject["value"].toString();
            QString description = jsonObject["description"].toString();
            QJsonObject error = newSchedule.create(scheduleUUID,userID,pinID,scheduleName,minute,hour,dayOfMonth,month,dayOfWeek,timeZone,value,description);
            QString cronSyntax = minute+" "+hour+" "+dayOfMonth+" "+month+" "+dayOfWeek+" *";
            emit createNewCron(scheduleUUID,cronSyntax,UUID,value,userID);
            errorArray.append(error);
            Log log(&db);
            log.create(userID,"Schedule "+jsonObject["scheduleName"].toString()+" has been created");
        }
    }

    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject ScheduleController::editSchedule(QJsonObject json, int userID)
{
    Schedule schedule(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["editSchedule"].toArray();
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
            int scheduleID = jsonObject["scheduleID"].toInt();
            schedule.read("scheduleID='"+QString::number(scheduleID)+"'");
            if(schedule.mSchedules.size() != 1){
                error["error"] = "schedule "+json["schedule"].toString()+" is not valid";
                error["errorCode"] = "9";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
            }
            else {
                QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
                int pinID = getPinIDbyUUID(UUID);
                QString scheduleName = jsonObject["scheduleName"].toString();
                QString minute = jsonObject["minute"].toString();
                QString hour = jsonObject["hour"].toString();
                QString dayOfMonth = jsonObject["dayOfMonth"].toString();
                QString month = jsonObject["month"].toString();
                QString dayOfWeek = jsonObject["dayOfWeek"].toString();
                QString timeZone = jsonObject["timeZone"].toString();
                QString value = jsonObject["value"].toString();
                QString description = jsonObject["description"].toString();
                error = schedule.update(scheduleID,userID,pinID,scheduleName,minute,hour,dayOfMonth,month,dayOfWeek,timeZone,value,description);
                QString cronSyntax = minute+" "+hour+" "+dayOfMonth+" "+month+" "+dayOfWeek+" *";
                emit editCron(schedule.mSchedules.at(0).scheduleUUID,cronSyntax,UUID,value,userID);
                Log log(&db);
                log.create(userID,"Schedule "+jsonObject["scheduleName"].toString()+" has been edited");
            }
            errorArray.append(error);
            notificationArray.append(notificationArray);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject ScheduleController::deleteSchedule(QJsonObject json, int userID)
{
    Schedule schedule(&db);
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    jsonArray = json["deleteSchedule"].toArray();
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
            int scheduleID = jsonObject["scheduleID"].toInt();
            schedule.read("scheduleID='"+QString::number(scheduleID)+"'");
            if((schedule.mSchedules.size() != 1) && (schedule.mSchedules.at(0).userID != userID)){
                error["error"] = "scheduleID "+json["scheduleID"].toString()+" is not valid";
                error["errorCode"] = "9";
                notification["title"]="Error";
                notification["description"] = error["error"].toString();
            }
            else {
                error = schedule.deletes("scheduleID='"+QString::number(scheduleID)+"'");
                Log log(&db);
                log.create(userID,"Schedule "+schedule.mSchedules.at(0).scheduleName+" has been deleted");
                emit deleteCron(schedule.mSchedules.at(0).scheduleUUID);
            }
            errorArray.append(error);
            notificationArray.append(notificationArray);
        }
    }
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

QJsonObject ScheduleController::getScheduleList(int userID)
{
    QJsonObject response;
    QJsonArray jsonArray,errorArray,notificationArray;
    Schedule schedule(&db);
    QJsonObject error = schedule.read("Schedule.userID='"+QString::number(userID)+"'");
    errorArray.append(error);
    if(schedule.mSchedules.size()<1){
        QJsonObject error,notification;
        error["error"] = "you do not have any scheduled item. please create one";
        error["errorCode"] = "7";
        notification["title"]="Error";
        notification["description"] = error["error"].toString();
        errorArray.append(error);
        notificationArray.append(notification);
    }
    else {
        for (int i = 0;i<schedule.mSchedules.size();i++) {
            QJsonObject jsonObject;
            jsonObject["scheduleID"] = schedule.mSchedules.at(i).scheduleID;
            jsonObject["userID"] = schedule.mSchedules.at(i).userID;
            jsonObject["pinUUID"] = schedule.mSchedules.at(i).pinUUID.toString(QUuid::WithoutBraces);
            jsonObject["scheduleName"] = schedule.mSchedules.at(i).scheduleName;
            jsonObject["minute"] = schedule.mSchedules.at(i).minute;
            jsonObject["hour"] = schedule.mSchedules.at(i).hour;
            jsonObject["dayOfMonth"] = schedule.mSchedules.at(i).dayOfMonth;
            jsonObject["month"] = schedule.mSchedules.at(i).month;
            jsonObject["dayOfWeek"] = schedule.mSchedules.at(i).dayOfWeek;
            jsonObject["timeZone"] = schedule.mSchedules.at(i).timeZone;
            jsonObject["value"] = schedule.mSchedules.at(i).value;
            jsonObject["description"] = schedule.mSchedules.at(i).description;
            jsonArray.append(jsonObject);
        }
    }
    response["scheduleList"] = jsonArray;
    response["error"] = errorArray;
    response["notification"] = notificationArray;
    return response;
}

void ScheduleController::initAllCron()
{
    Schedule theSchedule(&db);
    theSchedule.read();
    if(theSchedule.mSchedules.size()>0){
        for (int i = 0;i<theSchedule.mSchedules.size();i++) {
            QString cronSyntax = theSchedule.mSchedules.at(i).minute+" "+theSchedule.mSchedules.at(i).hour+" "+theSchedule.mSchedules.at(i).dayOfMonth+" "+theSchedule.mSchedules.at(i).month+" "+theSchedule.mSchedules.at(i).dayOfWeek+" *";
            emit createNewCron(theSchedule.mSchedules.at(i).scheduleUUID,cronSyntax,theSchedule.mSchedules.at(i).pinUUID,theSchedule.mSchedules.at(i).value,theSchedule.mSchedules.at(i).userID);
        }
    }
}

int ScheduleController::getPinIDbyUUID(QUuid UUID)
{
    Pin pin(&db);
    pin.read("Pin.UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"')");
    if(pin.mPins.size()!=1){
        return 0;
    }
    else return  pin.mPins.at(0).pinID;
}

void ScheduleController::deletedPin(QUuid pinUUID, int userID)
{
    Schedule schedule(&db);
    schedule.read("Pin.userID='"+QString::number(userID)+"'");
    if(schedule.mSchedules.size()<1){
        QTextStream(stdout) << "\nSchedule with pinUUID : " << pinUUID.toString(QUuid::WithoutBraces) << " is not avaiable.";
    }
    else {
        for (int i = 0;i<schedule.mSchedules.size();i++) {
            if(schedule.mSchedules.at(i).pinUUID == pinUUID){
                QJsonObject json;
                QJsonArray array;
                QJsonObject jsonObject;
                jsonObject["scheduleID"] = schedule.mSchedules.at(i).scheduleID;
                array.append(jsonObject);
                json["deleteSchedule"] = array;
                deleteSchedule(json,userID);
            }
        }
    }
}
