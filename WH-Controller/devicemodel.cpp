#include "devicemodel.h"
#include "devicelist.h"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const DeviceItem item = mList->items().at(index.row());
    switch(role){
    case ValueRole:
        return QVariant(item.value);
    case UuidRole :
        return QVariant(item.uuid);
    case TypeRole :
        return QVariant(item.type);
    case GroupRole :
        return QVariant(item.group);
    case NameRole :
        return QVariant(item.name);
    case OwnerEmailRole :
        return QVariant(item.ownerEmail);
    }
    return QVariant();
}

bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    DeviceItem item = mList->items().at(index.row());
    switch(role){
    case ValueRole:
        item.value = value.toString();
        break;
    }
    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags DeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ValueRole] = "value";
    names[UuidRole] = "uuid";
    names[TypeRole] = "type";
    names[GroupRole] = "group";
    names[NameRole] = "name";
    names[OwnerEmailRole] = "ownerEmail";
    return names;
}

DeviceList *DeviceModel::list() const
{
    return mList;
}

void DeviceModel::setList(DeviceList *list)
{
    beginResetModel();

    if(mList)
        mList->disconnect(this);

    mList = list;

    if(mList){
        connect(mList, &DeviceList::preItemAppended, this, [=](){
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(),index,index);
        });
        connect(mList, &DeviceList::postItemAppended, this, [=](){
            endInsertRows();
        });

        connect(mList, &DeviceList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(),index,index);
        });
        connect(mList, &DeviceList::postItemRemoved, this, [=](){
            endRemoveRows();
        });
    }

    endResetModel();
}
