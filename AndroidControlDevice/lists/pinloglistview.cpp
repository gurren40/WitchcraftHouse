#include "pinloglistview.h"
PinLogListView::PinLogListView(QObject *parent) : QObject(parent)
{

}

QVector<pinLogItem> PinLogListView::items() const
{
    return mItems;
}

void PinLogListView::setPinLogItems(const QVector<pinLogItem> &pinLogItems)
{
    emit preItemDataChanged();
    mItems = pinLogItems;
    emit postItemDataChanged();
}

bool PinLogListView::setItemAt(int index, const pinLogItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}
