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

RemoteReplica *DeviceList::remote() const
{
    return m_remote;
}

void DeviceList::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void DeviceList::getDeviceList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getDeviceList"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void DeviceList::createNewDevice(QVariant deviceName, QVariant description)
{
    //QJsonObject error = device.create(newUUID,userID,jsonObject["deviceName"].toString(),jwt.getToken(),0,jsonObject["description"].toString());
    QJsonObject jsonObj;
    jsonObj["deviceName"] = deviceName.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewDevice"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void DeviceList::editDevice(QVariant deviceID, QVariant deviceUUID, QVariant deviceName, QVariant description)
{
    //error = device.update(jsonObject["deviceID"].toInt(),QUuid::fromString(jsonObject["deviceUUID"].toString()),userID,jsonObject["deviceName"].toString(),device.mDevices.at(0).deviceToken,device.mDevices.at(0).isDeviceOnline,jsonObject["description"].toString());
    QJsonObject jsonObj;
    jsonObj["deviceID"] = deviceID.toInt();
    jsonObj["deviceUUID"] = deviceUUID.toString();
    jsonObj["deviceName"] = deviceName.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["editDevice"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void DeviceList::deleteDevice(QVariant deviceID)
{
    QJsonObject jsonObj;
    jsonObj["deviceID"] = deviceID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteDevice"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

QVariant DeviceList::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject DeviceList::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}

