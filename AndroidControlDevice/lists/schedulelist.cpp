#include "schedulelist.h"

ScheduleList::ScheduleList(QObject *parent) : QObject(parent)
{
    //mItems.append({ true, QStringLiteral("Wash the car") });
    //mItems.append({ false, QStringLiteral("Fix the sink") });
    ScheduleItem item;
    item.scheduleID = 1;
    item.scheduleUUID = "scheduleUUID";
    item.userID = 2;
    item.userName = "userName";
    item.pinID = 3;
    item.pinUUID = "pinUUID";
    item.pinName = "pinName";
    item.scheduleName = "scheduleName";
    item.minute = "minute";
    item.hour = "hour";
    item.dayOfMonth = "dayOfMonth";
    item.month = "month";
    item.dayOfWeek = "dayOfWeek";
    item.timeZone = "timeZone";
    item.value = "value";
    item.description = "description";
    ScheduleItem item2;
    item2 = item;
    mItems.append(item);
    mItems.append(item2);
    mItems.append(item);
    mItems.append(item2);
}

QVector<ScheduleItem> ScheduleList::items() const
{
    return mItems;
}

bool ScheduleList::setItemAt(int index, const ScheduleItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void ScheduleList::setScheduleList(QJsonObject json)
{
    QJsonArray jsonArray = json.value("scheduleList").toArray();
    emit preItemsResetRemove(mItems.size());
    mItems.clear();
    emit postItemResetRemove();
    emit preItemsResetAppend(jsonArray.size());
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject jsonItem = jsonArray.at(i).toObject();
        ScheduleItem item;
        item.scheduleID = jsonItem["scheduleID"].toInt();
        item.scheduleUUID = jsonItem["scheduleUUID"].toString();
        item.userID = jsonItem["userID"].toInt();
        item.userName = jsonItem["userName"].toString();
        item.pinID = jsonItem["pinID"].toInt();
        item.pinUUID = jsonItem["pinUUID"].toString();
        item.pinName = jsonItem["pinName"].toString();
        item.scheduleName = jsonItem["scheduleName"].toString();
        item.minute = jsonItem["minute"].toString();
        item.hour = jsonItem["hour"].toString();
        item.dayOfMonth = jsonItem["dayOfMonth"].toString();
        item.month = jsonItem["month"].toString();
        item.dayOfWeek = jsonItem["dayOfWeek"].toString();
        item.timeZone = jsonItem["timeZone"].toString();
        item.value = jsonItem["value"].toString();
        item.description = jsonItem["description"].toString();
        mItems.append(item);
    }
    postItemResetAppend();
}

RemoteReplica *ScheduleList::remote() const
{
    return m_remote;
}

void ScheduleList::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void ScheduleList::getScheduleList()
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

void ScheduleList::createNewSchedule(QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description)
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

void ScheduleList::editSchedule(QVariant scheduleID, QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description)
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

void ScheduleList::deleteSchedule(QVariant scheduleID)
{
    QJsonObject jsonObj;
    jsonObj["scheduleID"] = scheduleID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteSchedule"] = jsonArray;
    m_remote->sendToServer(toSend);
}
