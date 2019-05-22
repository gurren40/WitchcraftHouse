#include "loglistview.h"
LogListView::LogListView(QObject *parent) : QObject(parent)
{

}

QVector<logItem> LogListView::items() const
{
    return mItems;
}

void LogListView::setLogItems(const QVector<logItem> &logItems)
{
    emit preItemDataChanged();
    mItems = logItems;
    emit postItemDataChanged();
}

bool LogListView::setItemAt(int index, const logItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    mItems[index] = item;
    return true;
}
