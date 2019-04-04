#include "pintypelist.h"

PinTypeList::PinTypeList(QObject *parent) : QObject(parent)
{
    mItems.append({ 0, QStringLiteral("default") });
    mItems.append({ 1, QStringLiteral("switch") });
    mItems.append({ 2, QStringLiteral("textout") });
    mItems.append({ 3, QStringLiteral("tempc") });
    mItems.append({ 4, QStringLiteral("tempf") });
    mItems.append({ 5, QStringLiteral("textfield") });
    mItems.append({ 6, QStringLiteral("spinbox") });
    mItems.append({ 7, QStringLiteral("textarea") });
    mItems.append({ 8, QStringLiteral("tubler") });
    mItems.append({ 9, QStringLiteral("combobox") });
}

QVector<PinTypeItem> PinTypeList::items() const
{
    return mItems;
}

bool PinTypeList::setItemAt(int index, const PinTypeItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    const PinTypeItem &oldItem = mItems.at(index);
    if (item.pinTypeID == oldItem.pinTypeID && item.pinTypeName == oldItem.pinTypeName)
        return false;

    mItems[index] = item;
    return true;
}

void PinTypeList::appendItem()
{
    emit preItemAppended();

    PinTypeItem item;
    mItems.append(item);

    emit postItemAppended();
}
