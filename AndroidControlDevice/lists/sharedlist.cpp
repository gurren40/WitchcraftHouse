#include "sharedlist.h"

SharedList::SharedList(QObject *parent) : QObject(parent)
{
    //mItems.append({ true, QStringLiteral("Wash the car") });
    //mItems.append({ false, QStringLiteral("Fix the sink") });
    SharedItem item;
    item.sharedID = 1;
    item.sharedTo = "sharedTo";
    item.sharedToName = "sharedToName";
    item.sharedType = true;
    item.groupID = 2;
    item.groupName = "groupName";
    item.pinUUID = "pinUUID";
    item.pinName = "pinName";
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
    emit preItemsResetRemove(mItems.size());
    mItems.clear();
    emit postItemResetRemove();
    emit preItemsResetAppend(jsonArray.size());
    for(int i=0;i<jsonArray.size();i++){
        QJsonObject jsonItem = jsonArray.at(i).toObject();
        SharedItem item;
        item.sharedID = jsonItem["sharedID"].toInt();
        item.sharedTo = jsonItem["sharedTo"].toString();
        item.sharedToName = jsonItem["sharedToName"].toString();
        item.sharedType = jsonItem["sharedType"].toBool();
        item.groupID = jsonItem["groupID"].toInt();
        item.groupName = jsonItem["groupName"].toString();
        item.pinUUID = jsonItem["pinUUID"].toString();
        item.pinName = jsonItem["pinName"].toString();
        item.sharedName = jsonItem["sharedName"].toString();
        item.description = jsonItem["description"].toString();
        mItems.append(item);
    }
    postItemResetAppend();
}
