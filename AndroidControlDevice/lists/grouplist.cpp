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
    item.iconName = "iconName";
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
    QJsonArray jsonArray = json.value("GroupList").toArray();
    emit preItemsResetRemove(mItems.size());
    mItems.clear();
    emit postItemResetRemove();
    emit preItemsResetAppend(jsonArray.size());
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
    postItemResetAppend();
}
