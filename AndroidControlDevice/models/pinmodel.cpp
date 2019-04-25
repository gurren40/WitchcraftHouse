#include "pinmodel.h"
#include "lists/pinlist.h"

PinModel::PinModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int PinModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant PinModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const PinItem item = mList->items().at(index.row());
    switch (role) {
//    case DoneRole:
//        return QVariant(item.done);
//    case DescriptionRole:
//        return QVariant(item.description);
    case pinIDRole:
        return QVariant(item.pinID);
    case UUIDRole:
        return QVariant(item.UUID);
    case userIDRole:
        return QVariant(item.userID);
    case userNameRole:
        return QVariant(item.userName);
    case groupIDRole:
        return QVariant(item.groupID);
    case groupNameRole:
        return QVariant(item.groupName);
    case deviceIDRole:
        return QVariant(item.deviceID);
    case deviceNameRole:
        return QVariant(item.deviceName);
    case iconIDRole:
        return QVariant(item.iconID);
    case iconNameRole:
        return QVariant(item.iconName);
    case pinTypeIDRole:
        return QVariant(item.pinTypeID);
    case pinTypeNameRole:
        return QVariant(item.pinTypeName);
    case pinNameRole:
        return QVariant(item.pinName);
    case valueRole:
        return QVariant(item.value);
    case optionRole:
        return QVariant(item.option);
    case descriptionRole:
        return QVariant(item.description);
    }

    return QVariant();
}

bool PinModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    PinItem item = mList->items().at(index.row());
    switch (role) {
    case pinIDRole:
        item.pinID = value.toBool();
        break;
    case UUIDRole:
        item.UUID = value.toString();
        break;
    case userIDRole:
        item.userID = value.toInt();
        break;
    case userNameRole:
        item.userName = value.toString();
        break;
    case groupIDRole:
        item.groupID = value.toInt();
        break;
    case groupNameRole:
        item.groupName = value.toString();
        break;
    case deviceIDRole:
        item.deviceID = value.toInt();
        break;
    case deviceNameRole:
        item.deviceName = value.toString();
        break;
    case iconIDRole:
        item.iconID = value.toInt();
        break;
    case iconNameRole:
        item.iconName = value.toString();
        break;
    case pinTypeIDRole:
        item.pinTypeID = value.toInt();
        break;
    case pinTypeNameRole:
        item.pinTypeName = value.toString();
        break;
    case pinNameRole:
        item.pinName = value.toString();
        break;
    case valueRole:
        item.value = value.toString();
        break;
    case optionRole:
        item.option = value.toString();
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

Qt::ItemFlags PinModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PinModel::roleNames() const
{
    QHash<int, QByteArray> names;
//    names[DoneRole] = "done";
//    names[DescriptionRole] = "description";
    //int pinID;
    names[pinIDRole] = "pinID";
    //QString UUID;
    names[UUIDRole] = "UUID";
    //int userID;
    names[userIDRole] = "userID";
    //QString userName;
    names[userNameRole] = "userName";
    //int groupID;
    names[groupIDRole] = "groupID";
    //QString groupName;
    names[groupNameRole] = "groupName";
    //int deviceID;
    names[deviceIDRole] = "deviceID";
    //QString deviceName;
    names[deviceNameRole] = "deviceName";
    //int iconID;
    names[iconIDRole] = "iconID";
    //QString iconName;
    names[iconNameRole] = "iconName";
    //int pinTypeID;
    names[pinTypeIDRole] = "pinTypeID";
    //QString pinTypeName;
    names[pinTypeNameRole] = "pinTypeName";
    //QString pinName;
    names[pinNameRole] = "pinName";
    //QString value;
    names[valueRole] = "value";
    //QString option;
    names[optionRole] = "option";
    //QString description;
    names[descriptionRole] = "description";
    return names;
}

PinList *PinModel::list() const
{
    return mList;
}

void PinModel::setList(PinList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {

        //append item
        connect(mList, &PinList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &PinList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        //remove item
        connect(mList, &PinList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &PinList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &PinList::itemDataChanged, this, [=](int first, int last) {
            emit dataChanged(index(first),index(last),QVector<int>());
        });

        //setted pin value
        connect(mList, &PinList::preItemDataChanged, this, [=](){
            beginResetModel();
        });
        connect(mList, &PinList::postItemDataChanged, this, [=](){
            endResetModel();
        });
    }

    endResetModel();
}
