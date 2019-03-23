#include "device.h"

Device::Device(QObject *parent) : QObject(parent)
{

}

RemoteReplica *Device::remote() const
{
    return m_remote;
}

void Device::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void Device::getDeviceList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getDeviceList"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Device::createNewDevice(QVariant deviceName, QVariant description)
{
    //QJsonObject error = device.create(newUUID,userID,jsonObject["deviceName"].toString(),jwt.getToken(),0,jsonObject["description"].toString());
    QJsonObject jsonObj;
    jsonObj["deviceName"] = deviceName.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewDevice"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Device::editDevice(QVariant deviceID, QVariant deviceUUID, QVariant deviceName, QVariant description)
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
    m_remote->sendToServer(toSend);
}

void Device::deleteDevice(QVariant deviceID)
{
    QJsonObject jsonObj;
    jsonObj["deviceID"] = deviceID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteDevice"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Device::setPinValue(QVariant UUID, QVariant value)
{
    QJsonObject jsonObj;
    jsonObj["UUID"] = UUID.toString();
    jsonObj["value"] = value.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["setPinValue"] = jsonArray;
    m_remote->sendToServer(toSend);
}
