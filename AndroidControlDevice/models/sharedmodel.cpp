#include "sharedmodel.h"
#include "lists/sharedlist.h"

SharedModel::SharedModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int SharedModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant SharedModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const SharedItem item = mList->items().at(index.row());
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
    case sharedIDRole:
        return QVariant(item.sharedID);
//        QString sharedTo;
    case sharedToRole:
        return QVariant(item.sharedTo);
//        QString sharedToName;
    case sharedToNameRole:
        return QVariant(item.sharedToName);
//        bool sharedType;
    case sharedTypeRole:
        return QVariant(item.sharedType);
//        int groupID;
    case groupIDRole:
        return QVariant(item.groupID);
//        QString groupName;
    case groupNameRole:
        return QVariant(item.groupName);
//        QString pinUUID;
    case pinUUIDRole:
        return QVariant(item.pinUUID);
//        QString pinName;
    case pinNameRole:
        return QVariant(item.pinName);
//        QString sharedName;
    case sharedNameRole:
        return QVariant(item.sharedName);
//        QString description;
    case descriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool SharedModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    SharedItem item = mList->items().at(index.row());
    switch (role) {
//    case sharedIDRole:
//        item.sharedID = value.toBool();
//        break;
//    case UUIDRole:
//        item.UUID = value.toString();
//        break;
    case sharedIDRole:
        item.sharedID = value.toInt();
        break;
    case sharedToRole:
        item.sharedTo = value.toString();
        break;
    case sharedToNameRole:
        item.sharedToName = value.toString();
        break;
    case sharedTypeRole:
        item.sharedType = value.toBool();
        break;
    case groupIDRole:
        item.groupID = value.toInt();
        break;
    case groupNameRole:
        item.groupName = value.toString();
        break;
    case pinUUIDRole:
        item.pinUUID = value.toString();
        break;
    case pinNameRole:
        item.pinName = value.toString();
        break;
    case sharedNameRole:
        item.sharedName = value.toString();
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

Qt::ItemFlags SharedModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> SharedModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    names[DoneRole] = "done";
//    names[DescriptionRole] = "description";
//       int sharedID;
    names[sharedIDRole] = "sharedID";
//       QString sharedTo;
    names[sharedToRole] = "sharedTo";
//        QString sharedToName;
    names[sharedToNameRole] = "sharedToName";
//        bool sharedType;
    names[sharedTypeRole] = "sharedType";
//        int groupID;
    names[groupIDRole] = "groupID";
//        QString groupName;
    names[groupNameRole] = "groupName";
//        QString pinUUID;
    names[pinUUIDRole] = "pinUUID";
//        QString pinName;
    names[pinNameRole] = "pinName";
//        QString sharedName;
    names[sharedNameRole] = "sharedName";
//        QString description;
    names[descriptionRole] = "description";
    return names;
}

SharedList *SharedModel::list() const
{
    return mList;
}

void SharedModel::setList(SharedList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //delete semua item yang ada di list
        connect(mList, &SharedList::preItemsResetRemove,this, [=](int index){
            beginRemoveRows(QModelIndex(),0,index);
        });
        connect(mList, &SharedList::postItemResetRemove, this, [=]() {
            endRemoveRows();
        });

        //masukkan semua item dari list baru
        connect(mList, &SharedList::preItemsResetAppend,this, [=](int index){
            beginInsertRows(QModelIndex(),0,index);
        });
        connect(mList, &SharedList::postItemResetAppend, this, [=]() {
            endInsertRows();
        });
    }

    endResetModel();
}
