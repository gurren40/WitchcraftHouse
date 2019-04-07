#include "groupmodel.h"
#include "lists/grouplist.h"

GroupModel::GroupModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int GroupModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant GroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const GroupItem item = mList->items().at(index.row());
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
    case groupIDRole:
        return QVariant(item.groupID);
    case userIDRole:
        return QVariant(item.userID);
    case userNameRole:
        return QVariant(item.userName);
    case groupNameRole:
        return QVariant(item.groupName);
    case iconIDRole:
        return QVariant(item.iconID);
    case iconNameRole:
        return QVariant(item.iconName);
    case descriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool GroupModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    GroupItem item = mList->items().at(index.row());
    switch (role) {
    case groupIDRole:
        item.groupID = value.toInt();
        break;
    case userIDRole:
        item.userID = value.toInt();
        break;
    case userNameRole:
        item.userName = value.toString();
        break;
    case groupNameRole:
        item.groupName = value.toString();
        break;
    case iconIDRole:
        item.iconID = value.toInt();
        break;
    case iconNameRole:
        item.iconName = value.toString();
        break;
    case descriptionRole:
        item.description = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags GroupModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> GroupModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    names[DoneRole] = "done";
//    names[DescriptionRole] = "description";
    names[groupIDRole] = "groupID";
    names[userIDRole] = "userID";
    names[userNameRole] = "userName";
    names[groupNameRole] = "groupName";
    names[iconIDRole] = "iconID";
    names[iconNameRole] = "iconName";
    names[descriptionRole] = "description";
    return names;
}

GroupList *GroupModel::list() const
{
    return mList;
}

void GroupModel::setList(GroupList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //delete semua item yang ada di list
        connect(mList, &GroupList::preItemsResetRemove,this, [=](int index){
            beginRemoveRows(QModelIndex(),0,index);
        });
        connect(mList, &GroupList::postItemResetRemove, this, [=]() {
            endRemoveRows();
        });

        //masukkan semua item dari list baru
        connect(mList, &GroupList::preItemsResetAppend,this, [=](int index){
            beginInsertRows(QModelIndex(),0,index);
        });
        connect(mList, &GroupList::postItemResetAppend, this, [=]() {
            endInsertRows();
        });
        //try reset all we see?
        connect(mList, &GroupList::preItemDataChanged, this, [=](){
            beginResetModel();
        });
        connect(mList, &GroupList::postItemDataChanged, this, [=](){
            endResetModel();
        });
    }

    endResetModel();
}
