#include "devicelist.h"

DeviceList::DeviceList(QObject *parent) : QObject(parent)
{
    //mItems.append({ true, QStringLiteral("Wash the car") });
    //mItems.append({ false, QStringLiteral("Fix the sink") });
    DeviceItem item;
    item.deviceID = 1;
    item.deviceUUID = "deviceUUID";
    item.userID = 2;
    item.userName ="userName";
    item.deviceName = "deviceName";
    item.deviceToken = "deviceToken";
    item.isDeviceOnline = true;
    item.description = "description";
    DeviceItem item2;
    item2 = item;
    mItems.append(item);
    mItems.append(item2);
    mItems.append(item);
    mItems.append(item2);
}

QVector<DeviceItem> DeviceList::items() const
{
    return mItems;
}

bool DeviceList::setItemAt(int index, const DeviceItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void DeviceList::setDeviceList(QJsonObject json)
{
    QJsonArray jsonArray = json.value("DeviceList").toArray();
    emit preItemsResetRemove(mItems.size());
    mItems.clear();
    emit postItemResetRemove();
    emit preItemsResetAppend(jsonArray.size());
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject jsonItem = jsonArray.at(i).toObject();
        DeviceItem item;
        item.deviceID = jsonItem["deviceID"].toInt();
        item.deviceUUID = jsonItem["deviceUUID"].toString();
        item.userID = jsonItem["userID"].toInt();
        item.userName = jsonItem["userName"].toString();
        item.deviceName = jsonItem["deviceName"].toString();
        item.deviceToken = jsonItem["deviceToken"].toString();
        item.isDeviceOnline = jsonItem["isDeviceOnline"].toBool();
        item.description = jsonItem["description"].toString();
        mItems.append(item);
    }
    postItemResetAppend();
}
