#include "pinlogviewmodel.h"
#include "lists/pinloglistview.h"
#include "lists/logstructs.h"

PinLogViewModel::PinLogViewModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int PinLogViewModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant PinLogViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const pinLogItem item = mList->items().at(index.row());
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
//        int logID
    //        int pinLogID;
        case pinLogIDRole:
            return QVariant(item.pinLogID);
    //        int userID;
        case userIDRole:
            return QVariant(item.userID);
    //        QString userName;
        case userNameRole:
            return QVariant(item.userName);
    //        int pinID;
        case pinIDRole:
            return QVariant(item.pinID);
    //        QString pinName;
        case pinNameRole:
            return QVariant(item.pinName);
    //        QString pinUUID;
        case pinUUIDRole:
            return QVariant(item.pinUUID);
    //        int pinTypeID;
        case pinTypeIDRole:
            return QVariant(item.pinTypeID);
    //        QString pinTypeName;
        case pinTypeNameRole:
            return QVariant(item.pinTypeName);
    //        QString value;
        case valueRole:
            return QVariant(item.value);
    //        QString description;
        case descriptionRole:
            return QVariant(item.description);
    //        QDateTime timeStamp;
        case timeStampRole:
            return QVariant(item.timeStamp);
    }

    return QVariant();
}

bool PinLogViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    pinLogItem item = mList->items().at(index.row());
    switch (role) {
    //        int pinLogID;
        case pinLogIDRole:
            item.pinLogID = value.toInt();
            break;
    //        int userID;
        case userIDRole:
            item.userID = value.toInt();
            break;
    //        QString userName;
        case userNameRole:
            item.userName = value.toString();
            break;
    //        int pinID;
        case pinIDRole:
            item.pinID = value.toInt();
            break;
    //        QString pinName;
        case pinNameRole:
            item.pinName = value.toString();
            break;
    //        QString pinUUID;
        case pinUUIDRole:
            item.pinUUID = value.toString();
            break;
    //        int pinTypeID;
        case pinTypeIDRole:
            item.pinTypeID = value.toInt();
            break;
    //        QString pinTypeName;
        case pinTypeNameRole:
            item.pinTypeName = value.toString();
            break;
    //        QString value;
        case valueRole:
            item.value = value.toString();
            break;
    //        QString description;
        case descriptionRole:
            item.description = value.toString();
            break;
    //        QDateTime timeStamp;
        case timeStampRole:
            item.timeStamp = value.toDateTime();
            break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PinLogViewModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PinLogViewModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    int pinLogID;
    names[pinLogIDRole] = "pinLogID";
//    int userID;
    names[userIDRole] = "userID";
//    QString userName;
    names[userNameRole] = "userName";
//    int pinID;
    names[pinIDRole] = "pinID";
//    QString pinName;
    names[pinNameRole] = "pinName";
//    QString pinUUID;
    names[pinUUIDRole] = "pinUUID";
//    int pinTypeID;
    names[pinTypeIDRole] = "pinTypeID";
//    QString pinTypeName;
    names[pinTypeNameRole] = "pinTypeName";
//    QString value;
    names[valueRole] = "value";
//    QString description;
    names[descriptionRole] = "description";
//    QDateTime timeStamp;
    names[timeStampRole] = "timeStamp";
    return names;
}

PinLogListView *PinLogViewModel::list() const
{
    return mList;
}

void PinLogViewModel::setList(PinLogListView *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //delete semua item yang ada di list
//        connect(mList, &PinLogListView::preItemsResetRemove,this, [=](int index){
//            beginRemoveRows(QModelIndex(),0,index);
//        });
//        connect(mList, &PinLogListView::postItemResetRemove, this, [=]() {
//            endRemoveRows();
//        });

//        //masukkan semua item dari list baru
//        connect(mList, &PinLogListView::preItemsResetAppend,this, [=](int index){
//            beginInsertRows(QModelIndex(),0,index);
//        });
//        connect(mList, &PinLogListView::postItemResetAppend, this, [=]() {
//            endInsertRows();
//        });
        //try reset all we see?
        connect(mList, &PinLogListView::preItemDataChanged, this, [=](){
            beginResetModel();
        });
        connect(mList, &PinLogListView::postItemDataChanged, this, [=](){
            endResetModel();
        });
    }

    endResetModel();
}
