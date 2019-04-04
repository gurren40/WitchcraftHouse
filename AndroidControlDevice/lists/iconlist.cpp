#include "iconlist.h"

IconList::IconList(QObject *parent) : QObject(parent)
{
    mItems.append({ 0, QStringLiteral("default") });
    mItems.append({ 1, QStringLiteral("house") });
    mItems.append({ 2, QStringLiteral("lamp") });
    mItems.append({ 3, QStringLiteral("switch") });
    mItems.append({ 4, QStringLiteral("outlet") });
    mItems.append({ 5, QStringLiteral("fan") });
    mItems.append({ 6, QStringLiteral("thermometer") });
    mItems.append({ 7, QStringLiteral("lock") });
    mItems.append({ 8, QStringLiteral("key") });
    mItems.append({ 9, QStringLiteral("fire") });
}

QVector<IconItem> IconList::items() const
{
    return mItems;
}

bool IconList::setItemAt(int index, const IconItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const IconItem &oldItem = mItems.at(index);
    if (item.iconID == oldItem.iconID && item.iconName == oldItem.iconName)
        return false;

    mItems[index] = item;
    return true;
}

void IconList::appendItem()
{
    emit preItemAppended();

    IconItem item;
    mItems.append(item);

    emit postItemAppended();
}
