#include "group.h"

Group::Group(QObject *parent) : QObject(parent)
{

}

RemoteReplica *Group::getRemote() const
{
    return m_remote;
}

void Group::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void Group::getGroupList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getGroupList"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Group::createNewGroup(QVariant groupName, QVariant iconID, QVariant description)
{
    //QJsonObject error = device.create(newUUID,userID,jsonObject["deviceName"].toString(),jwt.getToken(),0,jsonObject["description"].toString());
    QJsonObject jsonObj;
    jsonObj["groupName"] = groupName.toString();
    jsonObj["iconID"] = iconID.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewGroup"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Group::editGroup(QVariant groupID, QVariant groupName, QVariant iconID, QVariant description)
{
    //error = device.update(jsonObject["deviceID"].toInt(),QUuid::fromString(jsonObject["deviceUUID"].toString()),userID,jsonObject["deviceName"].toString(),device.mDevices.at(0).deviceToken,device.mDevices.at(0).isDeviceOnline,jsonObject["description"].toString());
    QJsonObject jsonObj;
    jsonObj["groupID"] = groupID.toInt();
    jsonObj["iconID"] = iconID.toInt();
    jsonObj["groupName"] = groupName.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["editGroup"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Group::deleteGroup(QVariant groupID)
{
    QJsonObject jsonObj;
    jsonObj["groupID"] = groupID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteGroup"] = jsonArray;
    m_remote->sendToServer(toSend);
}
