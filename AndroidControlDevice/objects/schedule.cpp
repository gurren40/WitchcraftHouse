#include "schedule.h"

Schedule::Schedule(QObject *parent) : QObject(parent)
{

}

RemoteReplica *Schedule::remote() const
{
    return m_remote;
}

void Schedule::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void Schedule::getScheduleList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getScheduleList"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Schedule::createNewSchedule(QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description)
{
    QJsonObject jsonObj;
    jsonObj["scheduleName"] = scheduleName.toString();
    jsonObj["pinUUID"] = pinUUID.toString();
    jsonObj["minute"] = minute.toString();
    jsonObj["hour"] = hour.toString();
    jsonObj["dayOfMonth"] = dayOfMonth.toString();
    jsonObj["month"] = month.toString();
    jsonObj["dayOfWeek"] = dayOfWeek.toString();
    jsonObj["timeZone"] = timeZone.toString();
    jsonObj["value"] = value.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewSchedule"] = jsonArray;
    m_remote->sendToServer(toSend);
    /*
     * QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
     * QUuid scheduleUUID = QUuid::createUuid();
     * int pinID = getPinIDbyUUID(UUID);
     * QString scheduleName = json["scheduleName"].toString();
     * QString minute = json["minute"].toString();
     * QString hour = json["hour"].toString();
     * QString dayOfMonth = json["dayOfMonth"].toString();
     * QString month = json["month"].toString();
     * QString dayOfWeek = json["dayOfWeek"].toString();
     * QString timeZone = json["timeZone"].toString();
     * QString value = json["value"].toString();
     * QString description = json["description"].toString();
     */
}

void Schedule::editSchedule(QVariant scheduleID, QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description)
{
    QJsonObject jsonObj;
    jsonObj["scheduleID"] = scheduleID.toInt();
    jsonObj["scheduleName"] = scheduleName.toString();
    jsonObj["pinUUID"] = pinUUID.toString();
    jsonObj["minute"] = minute.toString();
    jsonObj["hour"] = hour.toString();
    jsonObj["dayOfMonth"] = dayOfMonth.toString();
    jsonObj["month"] = month.toString();
    jsonObj["dayOfWeek"] = dayOfWeek.toString();
    jsonObj["timeZone"] = timeZone.toString();
    jsonObj["value"] = value.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["editSchedule"] = jsonArray;
    m_remote->sendToServer(toSend);
//    QUuid UUID = QUuid::fromString(jsonObject["pinUUID"].toString());
//    int pinID = getPinIDbyUUID(UUID);
//    QString scheduleName = jsonObject["scheduleName"].toString();
//    QString minute = jsonObject["minute"].toString();
//    QString hour = jsonObject["hour"].toString();
//    QString dayOfMonth = jsonObject["dayOfMonth"].toString();
//    QString month = jsonObject["month"].toString();
//    QString dayOfWeek = jsonObject["dayOfWeek"].toString();
//    QString timeZone = jsonObject["timeZone"].toString();
//    QString value = jsonObject["value"].toString();
    //    QString description = jsonObject["description"].toString();
}

void Schedule::deleteSchedule(QVariant scheduleID)
{
    QJsonObject jsonObj;
    jsonObj["scheduleID"] = scheduleID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteSchedule"] = jsonArray;
    m_remote->sendToServer(toSend);
}
