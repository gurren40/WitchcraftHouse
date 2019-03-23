#include "pin.h"

Pin::Pin(QObject *parent) : QObject(parent)
{

}

RemoteReplica *Pin::remote() const
{
    return m_remote;
}

void Pin::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void Pin::getPinList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getPinList"] = jsonArray;
    m_remote->sendToServer(toSend);
    getSharedPinList();
}

void Pin::getSharedPinList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getSharedPinList"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Pin::createNewPin(QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description)
{
//    QJsonObject error = newPin.create(newUUID,userID,jsonObject["groupID"].toInt(),jsonObject["deviceID"].toInt(),jsonObject["iconID"].toInt(),jsonObject["pinTypeID"].toInt(),jsonObject["pinName"].toString()
//            ,jsonObject["value"].toString("0"),jsonObject["option"].toString(""),jsonObject["description"].toString(""));
    QJsonObject jsonObj;
    jsonObj["pinName"] = pinName.toString();
    jsonObj["groupID"] = groupID.toInt();
    jsonObj["deviceID"] = deviceID.toInt();
    jsonObj["iconID"] = iconID.toInt();
    jsonObj["pinTypeID"] = pinTypeID.toInt();
    jsonObj["value"] = value.toString();
    jsonObj["option"] = option.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewPin"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Pin::editPin(QVariant pinID, QVariant UUID, QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description)
{
    //error = pin.update(pin.mPins.at(0).pinID,pin.mPins.at(0).UUID,userID,jsonObject["groupID"].toInt(),jsonObject["deviceID"].toInt(),
    //jsonObject["iconID"].toInt(),jsonObject["pinTypeID"].toInt(),jsonObject["pinName"].toString(),pin.mPins.at(0).value,jsonObject["option"].toString(),jsonObject["description"].toString());
    QJsonObject jsonObj;
    jsonObj["pinID"] = pinID.toInt();
    jsonObj["UUID"] = UUID.toString();
    jsonObj["pinName"] = pinName.toString();
    jsonObj["groupID"] = groupID.toInt();
    jsonObj["deviceID"] = deviceID.toInt();
    jsonObj["iconID"] = iconID.toInt();
    jsonObj["pinTypeID"] = pinTypeID.toInt();
    jsonObj["value"] = value.toString();
    jsonObj["option"] = option.toString();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["editPin"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Pin::deletePin(QVariant UUID)
{
    QJsonObject jsonObj;
    jsonObj["UUID"] = UUID.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deletePin"] = jsonArray;
    m_remote->sendToServer(toSend);
}
