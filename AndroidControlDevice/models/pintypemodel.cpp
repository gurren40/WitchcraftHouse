#include "pintypemodel.h"

#include "lists/pintypelist.h"

PinTypeModel::PinTypeModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int PinTypeModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant PinTypeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const PinTypeItem item = mList->items().at(index.row());
    switch (role) {
    case PinTypeIDRole:
        return QVariant(item.pinTypeID);
    case PinTypeNameRole:
        return QVariant(item.pinTypeName);
    }

    return QVariant();
}

bool PinTypeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    PinTypeItem item = mList->items().at(index.row());
    switch (role) {
    case PinTypeIDRole:
        item.pinTypeID = value.toInt();
        break;
    case PinTypeNameRole:
        item.pinTypeName = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags PinTypeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> PinTypeModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[PinTypeIDRole] = "pinTypeID";
    names[PinTypeNameRole] = "pinTypeName";
    return names;
}

PinTypeList *PinTypeModel::list() const
{
    return mList;
}

void PinTypeModel::setList(PinTypeList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &PinTypeList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &PinTypeList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &PinTypeList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &PinTypeList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
