#include "logviewmodel.h"
#include "lists/loglistview.h"
#include "lists/logstructs.h"

LogViewModel::LogViewModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int LogViewModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant LogViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const logItem item = mList->items().at(index.row());
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
//        int logID
    case logIDrole:
        return QVariant(item.logID);
//        int userID;
    case userNameRole:
        return QVariant(item.userName);
//        QString userName;
    case descriptionRole:
        return QVariant(item.description);
//        QString description;
    case timeStampRole :
        return QVariant(item.timeStamp);
//        QDateTime timeStamp;
    }

    return QVariant();
}

bool LogViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    logItem item = mList->items().at(index.row());
    switch (role) {
    case logIDrole:
        item.logID = value.toInt();
        break;
//        int userID;
    case userNameRole:
        item.logID = value.toInt();
        break;
//        QString userName;
    case descriptionRole:
        item.logID = value.toInt();
        break;
//        QString description;
    case timeStampRole :
        item.logID = value.toInt();
        break;
//        QDateTime timeStamp;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags LogViewModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> LogViewModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    names[DoneRole] = "done";
//    names[DescriptionRole] = "description";
    names[logIDrole] = "logID";
    names[timeStampRole] = "timeStamp";
    names[userNameRole] = "userName";
    names[descriptionRole] = "description";
    return names;
}

LogListView *LogViewModel::list() const
{
    return mList;
}

void LogViewModel::setList(LogListView *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //delete semua item yang ada di list
//        connect(mList, &LogListView::preItemsResetRemove,this, [=](int index){
//            beginRemoveRows(QModelIndex(),0,index);
//        });
//        connect(mList, &LogListView::postItemResetRemove, this, [=]() {
//            endRemoveRows();
//        });

//        //masukkan semua item dari list baru
//        connect(mList, &LogListView::preItemsResetAppend,this, [=](int index){
//            beginInsertRows(QModelIndex(),0,index);
//        });
//        connect(mList, &LogListView::postItemResetAppend, this, [=]() {
//            endInsertRows();
//        });
        //try reset all we see?
        connect(mList, &LogListView::preItemDataChanged, this, [=](){
            beginResetModel();
        });
        connect(mList, &LogListView::postItemDataChanged, this, [=](){
            endResetModel();
        });
    }

    endResetModel();
}
