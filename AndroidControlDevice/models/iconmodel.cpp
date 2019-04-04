#include "iconmodel.h"

#include "lists/iconlist.h"

IconModel::IconModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int IconModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant IconModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const IconItem item = mList->items().at(index.row());
    switch (role) {
    case IconIDRole:
        return QVariant(item.iconID);
    case IconNameRole:
        return QVariant(item.iconName);
    }

    return QVariant();
}

bool IconModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    IconItem item = mList->items().at(index.row());
    switch (role) {
    case IconIDRole:
        item.iconID = value.toInt();
        break;
    case IconNameRole:
        item.iconName = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags IconModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> IconModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IconIDRole] = "iconID";
    names[IconNameRole] = "iconName";
    return names;
}

IconList *IconModel::list() const
{
    return mList;
}

void IconModel::setList(IconList *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &IconList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &IconList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &IconList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &IconList::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
