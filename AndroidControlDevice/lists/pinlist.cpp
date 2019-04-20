#include "pinlist.h"

PinItem setPin(QString pinName, QString userName, QString groupName, QString iconName, QString pinTypeName, QString value, QString option){
    PinItem item;
    item.UUID = "UUID";
    item.pinID = 1;
    item.value = value;
    item.iconID = 2;
    item.option = option;
    item.userID = 3;
    item.groupID = 4;
    item.pinName = pinName;
    item.deviceID = 5;
    item.iconName = iconName;
    item.userName = userName;
    item.groupName = groupName;
    item.pinTypeID = 6;
    item.deviceName = "deviceName";
    item.description = "description";
    item.pinTypeName = pinTypeName;
    return item;
}

PinList::PinList(QObject *parent) : QObject(parent)
{
    //mItems.append({ true, QStringLiteral("Wash the car") });
    //mItems.append({ false, QStringLiteral("Fix the sink") });
    PinItem item0 = setPin("default Example","User","Group 1","default","default","0","no");
    mItems.append(item0);
    PinItem item1 = setPin("switch Example","User","Group 1","switch","switch","1","0,1");
    mItems.append(item1);
    PinItem item2 = setPin("textout Example","User","Group 1","AC","textout","Suatu Keterangan","");
    mItems.append(item2);
    PinItem item3 = setPin("tempc Example","User","Group 1","thermometer","tempc","24","100");
    mItems.append(item3);
    PinItem item4 = setPin("textfield Example","User","Group 2","thermostat","textfield","Text yang bisa diedit","");
    mItems.append(item4);
    PinItem item5 = setPin("textarea Example","User","Group 2","bell","textarea","Text yang bisa diedit,\ndengan jangkauan yang lebih luas","");
    mItems.append(item5);
    PinItem item6 = setPin("tumbler Example","User","Group 2","sun","tumbler","6","11");
    mItems.append(item6);
    PinItem item7 = setPin("spinbox Example","User","Group 3","water","spinbox","7","0,12");
    mItems.append(item7);
    PinItem item8 = setPin("combobox Example","User","Group 3","lock","combobox","Green","Red,Green,Blue");
    mItems.append(item8);
    PinItem item9 = setPin("webview Example","User","Group 3","cctv","webview","https://www.archlinux.org","ArchLinuxForefah");
    mItems.append(item9);
    PinItem item10 = setPin("slider Example","User","Group 3","leaf","slider","2","0,10");
    mItems.append(item10);
//    mItems.append({ 0, QStringLiteral("default") });
//    mItems.append({ 1, QStringLiteral("switch") });
//    mItems.append({ 2, QStringLiteral("textout") });
//    mItems.append({ 3, QStringLiteral("tempc") });
//    mItems.append({ 4, QStringLiteral("textfield") });
//    mItems.append({ 5, QStringLiteral("textarea") });
//    mItems.append({ 6, QStringLiteral("tumbler") });
//    mItems.append({ 7, QStringLiteral("spinbox") });
//    mItems.append({ 8, QStringLiteral("combobox") });
//    mItems.append({ 9, QStringLiteral("webview") });
    //icon
//    mItems.append({ 0, QStringLiteral("default") });
//    mItems.append({ 1, QStringLiteral("house") });
//    mItems.append({ 2, QStringLiteral("lamp") });
//    mItems.append({ 3, QStringLiteral("switch") });
//    mItems.append({ 4, QStringLiteral("outlet") });
//    mItems.append({ 5, QStringLiteral("fan") });
//    mItems.append({ 6, QStringLiteral("thermometer") });
//    mItems.append({ 7, QStringLiteral("lock") });
//    mItems.append({ 8, QStringLiteral("key") });
//    mItems.append({ 9, QStringLiteral("fire") });
//    mItems.append({ 10, QStringLiteral("AC") });
//    mItems.append({ 11, QStringLiteral("cctv") });
//    mItems.append({ 12, QStringLiteral("bell") });
//    mItems.append({ 13, QStringLiteral("sun") });
//    mItems.append({ 14, QStringLiteral("moon") });
//    mItems.append({ 15, QStringLiteral("thermostat") });
//    mItems.append({ 16, QStringLiteral("power") });
//    mItems.append({ 17, QStringLiteral("door") });
//    mItems.append({ 18, QStringLiteral("water") });
//    mItems.append({ 19, QStringLiteral("leaf") });
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
    //emit preItemsResetRemove(mItems.size());
    emit preItemDataChanged();
    mItems.clear();
    //emit postItemResetRemove();
    //emit preItemsResetAppend(jsonArray.size());
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
    //emit postItemResetAppend();
    emit postItemDataChanged();
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
