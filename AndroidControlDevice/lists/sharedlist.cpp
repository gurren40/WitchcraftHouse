#include "sharedlist.h"

SharedList::SharedList(QObject *parent) : QObject(parent)
{
    SharedItem item;
    item.sharedID = 1;
    item.sharedTo = "sharedTo";
    item.sharedToName = "sharedToName";
    item.groupID = 2;
    item.groupName = "groupName";
    item.sharedName = "sharedName";
    item.description = "description";

    SharedItem item2;
    item2 = item;
    mItems.append(item);
    mItems.append(item2);
    mItems.append(item);
    mItems.append(item2);
}

QVector<SharedItem> SharedList::items() const
{
    return mItems;
}

bool SharedList::setItemAt(int index, const SharedItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}

void SharedList::setSharedList(QJsonObject json)
{
    QJsonArray jsonArray = json.value("sharedList").toArray();
    emit preItemDataChanged();
    //emit preItemsResetRemove(mItems.size());
    mItems.clear();
    //emit postItemResetRemove();
    //emit preItemsResetAppend(jsonArray.size());
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject jsonItem = jsonArray.at(i).toObject();
        SharedItem item;
        item.sharedID = jsonItem["sharedID"].toInt();
        item.sharedTo = jsonItem["sharedTo"].toString();
        item.sharedToName = jsonItem["sharedToName"].toString();
        item.groupID = jsonItem["groupID"].toInt();
        item.groupName = jsonItem["groupName"].toString();
        item.sharedName = jsonItem["sharedName"].toString();
        item.description = jsonItem["description"].toString();
        mItems.append(item);
    }
    //emit postItemResetAppend();
    emit postItemDataChanged();
}

RemoteReplica *SharedList::remote() const
{
    return m_remote;
}

void SharedList::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

void SharedList::getSharedList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getSharedList"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void SharedList::createNewShared(QVariant sharedName, QVariant sharedTo, QVariant groupID, QVariant description)
{
    QJsonObject jsonObj;
    jsonObj["sharedName"] = sharedName.toString();
    jsonObj["sharedTo"] = sharedTo.toString();
    jsonObj["groupID"] = groupID.toInt();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewShared"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void SharedList::editShared(QVariant sharedID, QVariant sharedName, QVariant sharedTo, QVariant groupID, QVariant description)
{
    QJsonObject jsonObj;
    jsonObj["sharedID"] = sharedID.toInt();
    jsonObj["sharedName"] = sharedName.toString();
    jsonObj["sharedTo"] = sharedTo.toString();
    jsonObj["groupID"] = groupID.toInt();
    jsonObj["description"] = description.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["editShared"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void SharedList::deleteShared(QVariant sharedID)
{
    QJsonObject jsonObj;
    jsonObj["sharedID"] = sharedID.toInt();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteShared"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}


QVariant SharedList::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject SharedList::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}


