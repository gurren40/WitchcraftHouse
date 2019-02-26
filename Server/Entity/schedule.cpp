#include "schedule.h"

Schedule::Schedule(QObject *parent) : QObject(parent)
{

}

Schedule::Schedule(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void Schedule::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject Schedule::create(QUuid scheduleUUID, int userID, int pinID, QString scheduleName, QString minute, QString hour, QString dayOfMonth, QString month, QString dayOfWeek, QString timeZone, QString value, QString description)
{
    QString textQuery = "INSERT INTO `Schedule` (`scheduleUUID`,`userID`,`pinID`,`scheduleName`,`minute`,`hour`,`dayOfMonth`,`month`,`dayOfWeek`,`timeZone`,`value`,`description`) VALUES (\
                        UuidToBin('"+scheduleUUID.toString(QUuid::WithoutBraces)+"'),\
                        '"+QString::number(userID)+"',\
                        '"+QString::number(pinID)+"',\
                        '"+scheduleName+"',\
                        '"+minute+"',\
                        '"+hour+"',\
                        '"+dayOfMonth+"',\
                        '"+month+"',\
                        '"+dayOfWeek+"',\
                        '"+timeZone+"',\
                        '"+value+"',\
                        '"+description+"');";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Schedule::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT *,UuidFromBin(Pin.UUID),UuidFromBin(Schedule.scheduleUUID) FROM  \
                         ((Schedule INNER JOIN User ON Schedule.userID = User.userID) \
                           INNER JOIN Pin ON Schedule.pinID = Pin.pinID \
                         ) WHERE "+wherequery+" ;";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mSchedules.clear();
            while (query.next()){
                schedule scheduleObject;
                scheduleObject.scheduleID = query.value("Schedule.scheduleID").toInt();
                scheduleObject.scheduleUUID = QUuid(query.value("UuidFromBin(Schedule.scheduleUUID)").toString());
                scheduleObject.userID = query.value("Schedule.userID").toInt();
                scheduleObject.userName = query.value("User.name").toString();
                scheduleObject.pinID = query.value("Schedule.pinID").toInt();
                scheduleObject.pinUUID = QUuid(query.value("UuidFromBin(Pin.UUID)").toString());
                scheduleObject.pinName = query.value("Pin.pinName").toString();
                scheduleObject.scheduleName = query.value("Schedule.scheduleName").toString();
                scheduleObject.minute = query.value("Schedule.minute").toString();
                scheduleObject.hour = query.value("Schedule.hour").toString();
                scheduleObject.dayOfMonth = query.value("Schedule.dayOfMonth").toString();
                scheduleObject.month = query.value("Schedule.month").toString();
                scheduleObject.dayOfWeek = query.value("Schedule.dayOfWeek").toString();
                scheduleObject.timeZone = query.value("Schedule.timeZone").toString();
                scheduleObject.value = query.value("Schedule.value").toString();
                scheduleObject.description = query.value("Schedule.description").toString();
                mSchedules.append(scheduleObject);
            }
            mSchedules.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Schedule::update(int scheduleID, int userID, int pinID, QString scheduleName, QString minute, QString hour, QString dayOfMonth, QString month, QString dayOfWeek, QString timeZone, QString value, QString description)
{
    QString textQuery = "UPDATE `Schedule` SET \
                        userID='"+QString::number(userID)+"',\
                        pinID='"+QString::number(pinID)+"',\
                        scheduleName='"+scheduleName+"',\
                        minute='"+minute+"',\
                        hour='"+hour+"',\
                        dayOfMonth='"+dayOfMonth+"',\
                        month='"+month+"',\
                        dayOfWeek='"+dayOfWeek+"',\
                        timeZone='"+timeZone+"',\
                        value='"+value+"',\
                        description='"+description+"' \
                        WHERE scheduleID='"+QString::number(scheduleID)+"';";

    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Schedule::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `Schedule` WHERE "+wherequery+";";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}
