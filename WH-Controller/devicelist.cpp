#include "devicelist.h"

DeviceList::DeviceList(QObject *parent) : QObject(parent)
{
    emit initRequestAllDevice();
}

QVector<DeviceItem> DeviceList::items() const
{
    return mItems;
}

bool DeviceList::setItemAt(int index, const DeviceItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const DeviceItem &oldItem = mItems.at(index);
    if (item.uuid == oldItem.uuid && item.value == oldItem.value)
        return false;

    mItems[index] = item;
    requestSetDeviceValue(item.uuid,item.value);
    return true;
}

void DeviceList::requestSetDeviceValue(QString uuid, QString value)
{
    QJsonObject json;
    json["toWhere"] = "toDevice";
    json["function"] = "requestSetDeviceValue";
    json["uuid"] = uuid;
    json["value"] = value;
    emit sendMessageToServer(json);
}

void DeviceList::initRequestAllDevice()
{
    QJsonObject json;
    json["toWhere"] = "toDevice";
    json["function"] = "getDeviceList";
    emit sendMessageToServer(json);
}

void DeviceList::rewriteAllItem(QJsonObject json)
{
    //int mItemSize = mItems.size();
    /*for(int i = 0; i < mItemSize; i++){
        removeItemAtIndex(i);
    }*/
    foreach (DeviceItem item, mItems) {
        removeItem(item);
    }

    QJsonArray array = json["DeviceList"].toArray();
    int mItemSize2 = array.size();
    for(int i=0; i< mItemSize2;i++){
        QJsonObject obj = array[i].toObject();
        DeviceItem item;
        item.uuid = obj["uuid"].toString();
        item.value = obj["value"].toString();
        item.type = obj["type"].toString();
        item.group = obj["group"].toString();
        item.name = obj["name"].toString();
        item.ownerEmail = obj["ownerEmail"].toString();
        appendItem(item);
    }
}

void DeviceList::appendItem(DeviceItem item)
{
    emit preItemAppended();

    mItems.append(item);

    emit postItemAppended();
}

void DeviceList::removeItem(DeviceItem item)
{
    for (int i = 0; i < mItems.size(); ){
        if(mItems.at(i).uuid == item.uuid){
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        }else{
            ++i;
        }
    }
}

void DeviceList::removeItemAtIndex(int index)
{
    emit preItemRemoved(index);

    mItems.removeAt(index);

    emit postItemRemoved();
}
