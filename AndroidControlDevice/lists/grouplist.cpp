#include "grouplist.h"

GroupList::GroupList(QObject *parent) : QObject(parent)
{
    //mItems.append({ true, QStringLiteral("Wash the car") });
    //mItems.append({ false, QStringLiteral("Fix the sink") });
    GroupItem item;
    item.groupID = 1;
    item.userID = 2;
    item.userName ="userName";
    item.groupName = "groupName";
    item.iconID = 3;
    item.iconName = "house";
    item.description = "description";
    GroupItem item2;
    item2 = item;
    mItems.append(item);
    mItems.append(item2);
    mItems.append(item);
    mItems.append(item2);
}

QVector<GroupItem> GroupList::items() const
{
    return mItems;
}

bool GroupList::setItemAt(int index, const GroupItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void GroupList::setGroupList(QJsonObject json)
{
    QJsonArray jsonArray = json.value("groupList").toArray();
    emit preItemDataChanged();
    //emit preItemsResetRemove(mItems.size());
    mItems.clear();
    //emit postItemResetRemove();
    //emit preItemsResetAppend(jsonArray.size());
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject jsonItem = jsonArray.at(i).toObject();
        GroupItem item;
        item.groupID = jsonItem["groupID"].toInt();
        item.userID = jsonItem["userID"].toInt();
        item.userName = jsonItem["userName"].toString();
        item.groupName = jsonItem["groupName"].toString();
        item.iconID = jsonItem["iconID"].toInt();
        item.iconName = jsonItem["iconName"].toString();
        item.description = jsonItem["description"].toString();
        mItems.append(item);
    }
    //emit postItemResetAppend();
    emit postItemDataChanged();
}

RemoteReplica *GroupList::getRemote() const
{
    return m_remote;
}

void GroupList::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void GroupList::getGroupList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getGroupList"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void GroupList::createNewGroup(QVariant groupName, QVariant iconID, QVariant description)
{
    //QJsonObject error = device.create(newUUID,userID,jsonObject["deviceName"].toString(),jwt.getToken(),0,jsonObject["description"].toString());
    QJsonObject jsonObj;
    jsonObj["groupName"] = groupName.toString();
    jsonObj["iconID"] = iconID.toInt();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewGroup"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void GroupList::editGroup(QVariant groupID, QVariant groupName, QVariant iconID, QVariant description)
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
    m_remote->sendToServer(jsonToVariant(toSend));
}

void GroupList::deleteGroup(QVariant groupID)
{
    QJsonObject jsonObj;
    jsonObj["groupID"] = groupID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteGroup"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

QVariant GroupList::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject GroupList::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}
