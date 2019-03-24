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
