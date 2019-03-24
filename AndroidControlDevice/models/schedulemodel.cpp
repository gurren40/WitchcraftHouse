#include "schedulemodel.h"
#include "lists/schedulelist.h"

ScheduleModel::ScheduleModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int ScheduleModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant ScheduleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ScheduleItem item = mList->items().at(index.row());
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
    case scheduleIDRole:
        return  QVariant(item.scheduleID);
    case scheduleUUIDRole:
        return QVariant(item.scheduleUUID);
    case userIDRole:
        return QVariant(item.userID);
    case userNameRole:
        return QVariant(item.userName);
    case pinIDRole:
        return QVariant(item.pinID);
    case pinUUIDRole:
        return QVariant(item.pinUUID);
    case pinNameRole:
        return QVariant(item.pinName);
    case scheduleNameRole:
        return QVariant(item.scheduleName);
    case minuteRole:
        return QVariant(item.minute);
    case hourRole:
        return QVariant(item.hour);
    case dayOfMonthRole:
        return QVariant(item.dayOfMonth);
    case monthRole:
        return QVariant(item.month);
    case dayOfWeekRole:
        return QVariant(item.dayOfWeek);
    case timeZoneRole:
        return QVariant(item.timeZone);
    case valueRole:
        return QVariant(item.value);
    case descriptionRole:
        return QVariant(item.description);
    }
    return QVariant();
}

bool ScheduleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    ScheduleItem item = mList->items().at(index.row());
    switch (role) {
//    case scheduleIDRole:
//        item.scheduleID = value.toBool();
//        break;
    case scheduleIDRole:
        item.scheduleID = value.toInt();
        break;
    case scheduleUUIDRole:
        item.scheduleUUID = value.toString();
        break;
    case userIDRole:
        item.userID = value.toInt();
        break;
    case userNameRole:
        item.userName = value.toString();
        break;
    case pinIDRole:
        item.pinID = value.toInt();
        break;
    case pinUUIDRole:
        item.pinUUID = value.toString();
        break;
    case pinNameRole:
        item.pinName = value.toString();
        break;
    case scheduleNameRole:
        item.scheduleName = value.toString();
        break;
    case minuteRole:
        item.minute = value.toString();
        break;
    case hourRole:
        item.hour = value.toString();
        break;
    case dayOfMonthRole:
        item.dayOfMonth = value.toString();
        break;
    case monthRole:
        item.month = value.toString();
        break;
    case dayOfWeekRole:
        item.dayOfWeek = value.toString();
        break;
    case timeZoneRole:
        item.timeZone = value.toString();
        break;
    case valueRole:
        item.value = value.toString();
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

Qt::ItemFlags ScheduleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ScheduleModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    names[DoneRole] = "done";
//    names[DescriptionRole] = "description";
    names[scheduleIDRole] = "scheduleID";
//        QString scheduleUUID;
    names[scheduleUUIDRole] = "scheduleUUID";
//        int userID;
    names[userIDRole] = "userID";
//        QString userName;
    names[userNameRole] = "userName";
//        int pinID;
    names[pinIDRole] = "pinID";
//        QString pinUUID;
    names[pinUUIDRole] = "pinUUID";
//        QString pinName;
    names[pinNameRole] = "pinName";
//        QString scheduleName;
    names[scheduleNameRole] = "scheduleName";
//        QString minute;
    names[minuteRole] = "minute";
//        QString hour;
    names[hourRole] = "hour";
//        QString dayOfMonth;
    names[dayOfMonthRole] = "dayOfMonth";
//        QString month;
    names[monthRole] = "month";
//        QString dayOfWeek;
    names[dayOfWeekRole] = "dayOfWeek";
//        QString timeZone;
    names[timeZoneRole] = "timeZone";
//        QString value;
    names[valueRole] = "value";
//        QString description;
    names[descriptionRole] = "description";
    return names;
}

ScheduleList *ScheduleModel::list() const
{
    return mList;
}

void ScheduleModel::setList(ScheduleList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //delete semua item yang ada di list
        connect(mList, &ScheduleList::preItemsResetRemove,this, [=](int index){
            beginRemoveRows(QModelIndex(),0,index);
        });
        connect(mList, &ScheduleList::postItemResetRemove, this, [=]() {
            endRemoveRows();
        });

        //masukkan semua item dari list baru
        connect(mList, &ScheduleList::preItemsResetAppend,this, [=](int index){
            beginInsertRows(QModelIndex(),0,index);
        });
        connect(mList, &ScheduleList::postItemResetAppend, this, [=]() {
            endInsertRows();
        });
    }

    endResetModel();
}
