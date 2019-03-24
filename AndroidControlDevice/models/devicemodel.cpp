#include "devicemodel.h"
#include "lists/devicelist.h"

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
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
    case deviceIDRole:
        return QVariant(item.deviceID);
    case deviceUUIDRole:
        return QVariant(item.deviceUUID);
    case userIDRole:
        return QVariant(item.userID);
    case userNameRole:
        return QVariant(item.userName);
    case deviceNameRole:
        return QVariant(item.deviceName);
    case deviceTokenRole:
        return QVariant(item.deviceToken);
    case isDeviceOnlineRole:
        return QVariant(item.isDeviceOnline);
    case descriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool DeviceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    DeviceItem item = mList->items().at(index.row());
    switch (role) {
    case deviceIDRole:
        item.deviceID = value.toInt();
        break;
    case deviceUUIDRole:
        item.deviceUUID = value.toString();
        break;
    case userIDRole:
        item.userID = value.toInt();
        break;
    case userNameRole:
        item.userName = value.toString();
        break;
    case deviceNameRole:
        item.deviceName = value.toString();
        break;
    case deviceTokenRole:
        item.deviceToken = value.toString();
        break;
    case isDeviceOnlineRole:
        item.isDeviceOnline = value.toBool();
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

Qt::ItemFlags DeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    names[DoneRole] = "done";
//    names[DescriptionRole] = "description";
    names[deviceIDRole] = "deviceID";
    names[deviceUUIDRole] = "deviceUUID";
    names[userIDRole] = "userID";
    names[userNameRole] = "userName";
    names[deviceNameRole] = "deviceName";
    names[deviceTokenRole] = "deviceToken";
    names[isDeviceOnlineRole] = "isDeviceOnline";
    names[descriptionRole] = "description";
    return names;
}

DeviceList *DeviceModel::list() const
{
    return mList;
}

void DeviceModel::setList(DeviceList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //delete semua item yang ada di list
        connect(mList, &DeviceList::preItemsResetRemove,this, [=](int index){
            beginRemoveRows(QModelIndex(),0,index);
        });
        connect(mList, &DeviceList::postItemResetRemove, this, [=]() {
            endRemoveRows();
        });

        //masukkan semua item dari list baru
        connect(mList, &DeviceList::preItemsResetAppend,this, [=](int index){
            beginInsertRows(QModelIndex(),0,index);
        });
        connect(mList, &DeviceList::postItemResetAppend, this, [=]() {
            endInsertRows();
        });
    }

    endResetModel();
}
