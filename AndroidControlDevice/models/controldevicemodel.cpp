#include "controldevicemodel.h"
#include "lists/controldevicelist.h"

ControlDeviceModel::ControlDeviceModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int ControlDeviceModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant ControlDeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ControlDeviceItem item = mList->items().at(index.row());
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
    case controlDeviceIDRole:
        return QVariant(item.controlDeviceID);
    case userIDRole:
        return QVariant(item.userID);
    case userNameRole:
        return QVariant(item.userName);
    case controlDeviceNameRole:
        return QVariant(item.controlDeviceName);
    case controlDeviceTokenRole:
        return QVariant(item.controlDeviceToken);
    case isControlDeviceOnlineRole:
        return QVariant(item.isControlDeviceOnline);
    case expireDateRole:
        return QVariant(item.expireDate);
    }

    return QVariant();
}

bool ControlDeviceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    ControlDeviceItem item = mList->items().at(index.row());
    switch (role) {
    case controlDeviceIDRole:
        item.controlDeviceID = value.toString();
        break;
    case userIDRole:
        item.userID = value.toInt();
        break;
    case userNameRole:
        item.userName = value.toString();
        break;
    case controlDeviceNameRole:
        item.controlDeviceName = value.toString();
        break;
    case controlDeviceTokenRole:
        item.controlDeviceToken = value.toString();
        break;
    case isControlDeviceOnlineRole:
        item.isControlDeviceOnline = value.toBool();
        break;
    case expireDateRole:
        item.expireDate = value.toDate();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ControlDeviceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ControlDeviceModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    names[DoneRole] = "done";
//    names[DescriptionRole] = "description";
    names[controlDeviceIDRole] = "controlDeviceID";
    names[userIDRole] = "userID";
    names[userNameRole] = "userName";
    names[controlDeviceNameRole] = "controlDeviceName";
    names[controlDeviceTokenRole] = "controlDeviceToken";
    names[isControlDeviceOnlineRole] = "isControlDeviceOnline";
    names[expireDateRole] = "expireDate";
    return names;
}

ControlDeviceList *ControlDeviceModel::list() const
{
    return mList;
}

void ControlDeviceModel::setList(ControlDeviceList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //delete semua item yang ada di list
        connect(mList, &ControlDeviceList::preItemsResetRemove,this, [=](int index){
            beginRemoveRows(QModelIndex(),0,index);
        });
        connect(mList, &ControlDeviceList::postItemResetRemove, this, [=]() {
            endRemoveRows();
        });

        //masukkan semua item dari list baru
        connect(mList, &ControlDeviceList::preItemsResetAppend,this, [=](int index){
            beginInsertRows(QModelIndex(),0,index);
        });
        connect(mList, &ControlDeviceList::postItemResetAppend, this, [=]() {
            endInsertRows();
        });
        //try reset all we see?
        connect(mList, &ControlDeviceList::preItemDataChanged, this, [=](){
            beginResetModel();
        });
        connect(mList, &ControlDeviceList::postItemDataChanged, this, [=](){
            endResetModel();
        });
    }

    endResetModel();
}
