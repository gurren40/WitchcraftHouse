#include "pinlist.h"

PinList::PinList(QObject *parent) : QObject(parent)
{
    //mItems.append({ true, QStringLiteral("Wash the car") });
    //mItems.append({ false, QStringLiteral("Fix the sink") });
    PinItem item;
    item.UUID = "UUID";
    item.pinID = 1;
    item.value = "value";
    item.iconID = 2;
    item.option = "option";
    item.userID = 3;
    item.groupID = 4;
    item.pinName = "pinName";
    item.deviceID = 5;
    item.iconName = "iconName";
    item.userName = "userName";
    item.groupName = "groupName";
    item.pinTypeID = 6;
    item.deviceName = "deviceName";
    item.description = "description";
    item.pinTypeName = "pinTypeName";
    PinItem item2;
    item2 = item;
    mItems.append(item);
    mItems.append(item2);
    mItems.append(item);
    mItems.append(item2);
}

QVector<PinItem> PinList::items() const
{
    return mItems;
}

bool PinList::setItemAt(int index, const PinItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void PinList::setPinList(QJsonObject json)
{
    QJsonArray jsonArray = json.value("pinList").toArray();
    emit preItemsResetRemove(mItems.size());
    mItems.clear();
    emit postItemResetRemove();
    emit preItemsResetAppend(jsonArray.size());
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject jsonItem = jsonArray.at(i).toObject();
        PinItem item;
        item.UUID = jsonItem["UUID"].toString();
        item.pinID = jsonItem["pinID"].toInt();
        item.value = jsonItem["value"].toString();
        item.iconID = jsonItem["iconID"].toInt();
        item.option = jsonItem["option"].toString();
        item.userID = jsonItem["userID"].toInt();
        item.groupID = jsonItem["groupID"].toInt();
        item.pinName = jsonItem["pinName"].toString();
        item.deviceID = jsonItem["deviceID"].toInt();
        item.iconName = jsonItem["iconName"].toString();
        item.userName = jsonItem["userName"].toString();
        item.groupName = jsonItem["groupName"].toString();
        item.pinTypeID = jsonItem["pinTypeID"].toInt();
        item.deviceName = jsonItem["deviceName"].toString();
        item.description = jsonItem["description"].toString();
        item.pinTypeName = jsonItem["pinTypeName"].toString();
        mItems.append(item);
    }
    postItemResetAppend();
}
