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
    item.groupName = "Lol";
    item.pinTypeID = 6;
    item.deviceName = "deviceName";
    item.description = "description";
    item.pinTypeName = "switch";
    PinItem item2;
    item2 = item;
    item2.pinTypeName = "default";
    item2.groupName = "lil";
    PinItem item3 = item;
    item3.pinName = "Ruang Tengah";
    item3.groupName = "CCTV";
    item3.pinTypeName = "webview";
    item3.value = "http://192.168.0.4:8081/";
    PinItem item4 = item3;
    item4.pinName = "ArchLinux.org";
    item4.groupName = "Website";
    item4.pinTypeName = "webview";
    item4.value = "https://www.archlinux.org/";
    mItems.append(item);
    mItems.append(item2);
    mItems.append(item2);
    mItems.append(item);
    mItems.append(item3);
    mItems.append(item4);
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

void PinList::setPinList(QJsonObject json, bool isShared)
{
    QJsonArray jsonArray;
    if(isShared){
        jsonArray = json.value("sharedPinList").toArray();
    }
    else {
        jsonArray = json.value("pinList").toArray();
    }
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
    emit postItemResetAppend();
}

RemoteReplica *PinList::remote() const
{
    return m_remote;
}

void PinList::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void PinList::getPinList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getPinList"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
    getSharedPinList();
}

void PinList::getSharedPinList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getSharedPinList"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void PinList::createNewPin(QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description)
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
    m_remote->sendToServer(jsonToVariant(toSend));
}

void PinList::editPin(QVariant pinID, QVariant UUID, QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description)
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
    m_remote->sendToServer(jsonToVariant(toSend));
}

void PinList::deletePin(QVariant UUID)
{
    QJsonObject jsonObj;
    jsonObj["UUID"] = UUID.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deletePin"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void PinList::setPinValue(QVariant UUID, QVariant value)
{
    QJsonObject jsonObj;
    jsonObj["UUID"] = UUID.toString();
    jsonObj["value"] = value.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["setPinValue"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void PinList::settedPinValue(QJsonObject json)
{
    emit preItemDataChanged();
    QJsonArray jsonArray = json.value("settedPinValue").toArray();
    for (int i = 0;i<jsonArray.size();i++) {
        for(int j = 0;j<mItems.size();j++){
            if(mItems.at(j).UUID == jsonArray.at(i).toObject().value("UUID").toString()){
                PinItem item = mItems.at(j);
                item.value = jsonArray.at(i).toObject().value("value").toString();
                mItems[j] = item;
            }
        }
    }
    emit postItemDataChanged();
}

QVariant PinList::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject PinList::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}
