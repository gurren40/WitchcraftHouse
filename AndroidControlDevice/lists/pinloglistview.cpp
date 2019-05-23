#include "pinloglistview.h"
PinLogListView::PinLogListView(QObject *parent) : QObject(parent)
{
 dataType = 0;
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

void PinLogListView::setDataType(int value)
{
    dataType = value;
}

QVariant PinLogListView::readDayWeek(int day)
{
    if(dataType == 0){
        float totalValue = 0;
        float toReturn;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(day == mItems.at(i).timeStamp.date().dayOfWeek()){
                    totalValue = totalValue + mItems.at(i).value.toFloat();
                }
            }
            if(totalValue > 0){
                toReturn = totalValue / mItems.size();
            }
            else{
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return (toReturn);
    }
    else if(dataType == 1){
        qint64 toReturn;
        qint64 secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(day == mItems.at(i).timeStamp.date().dayOfWeek()){
                    if(mItems.at(i).value == "1"){
                        beforeIs1 = true;
                        timeStart = mItems.at(i).timeStamp;
                    }
                    else if(mItems.at(i).value == "0"){
                        if(beforeIs1){
                            secondElapsed = secondElapsed + timeStart.secsTo(mItems.at(i).timeStamp);
                            beforeIs1 = false;
                            hasValue = true;
                        }
                    }
                }
            }
            if(hasValue){
                if(secondElapsed > 0){
                    toReturn = secondElapsed / 3600;
                }
                else {
                    toReturn = 0;
                }
            }
            else {
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return toReturn;
    }
    else {
        return 0;
    }
}

QVariant PinLogListView::readDayMonth(int day)
{
    if(dataType == 0){
        float totalValue = 0;
        float toReturn;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(day == mItems.at(i).timeStamp.date().day()){
                    totalValue = totalValue + mItems.at(i).value.toFloat();
                }
            }
            if(totalValue > 0){
                toReturn = totalValue / mItems.size();
            }
            else{
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return (toReturn);
    }
    else if(dataType == 1){
        qint64 toReturn;
        qint64 secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(day == mItems.at(i).timeStamp.date().day()){
                    if(mItems.at(i).value == "1"){
                        beforeIs1 = true;
                        timeStart = mItems.at(i).timeStamp;
                    }
                    else if(mItems.at(i).value == "0"){
                        if(beforeIs1){
                            secondElapsed = secondElapsed + timeStart.secsTo(mItems.at(i).timeStamp);
                            beforeIs1 = false;
                            hasValue = true;
                        }
                    }
                }
            }
            if(hasValue){
                if(secondElapsed > 0){
                    toReturn = secondElapsed / 3600;
                }
                else {
                    toReturn = 0;
                }
            }
            else {
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return toReturn;
    }
    else {
        return 0;
    }
}

QVariant PinLogListView::readMonth(int month)
{
    if(dataType == 0){
        float totalValue = 0;
        float toReturn;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(month == mItems.at(i).timeStamp.date().month()){
                    totalValue = totalValue + mItems.at(i).value.toFloat();
                }
            }
            if(totalValue > 0){
                toReturn = totalValue / mItems.size();
            }
            else{
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return (toReturn);
    }
    else if(dataType == 1){
        qint64 toReturn;
        qint64 secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(month == mItems.at(i).timeStamp.date().month()){
                    if(mItems.at(i).value == "1"){
                        beforeIs1 = true;
                        timeStart = mItems.at(i).timeStamp;
                    }
                    else if(mItems.at(i).value == "0"){
                        if(beforeIs1){
                            secondElapsed = secondElapsed + timeStart.secsTo(mItems.at(i).timeStamp);
                            beforeIs1 = false;
                            hasValue = true;
                        }
                    }
                }
            }
            if(hasValue){
                if(secondElapsed > 0){
                    toReturn = secondElapsed / 3600;
                }
                else {
                    toReturn = 0;
                }
            }
            else {
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return toReturn;
    }
    else {
        return 0;
    }
}

QVariant PinLogListView::readYear(int year)
{
    if(dataType == 0){
        float totalValue = 0;
        float toReturn;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(year == mItems.at(i).timeStamp.date().year()){
                    totalValue = totalValue + mItems.at(i).value.toFloat();
                }
            }
            if(totalValue > 0){
                toReturn = totalValue / mItems.size();
            }
            else{
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return (toReturn);
    }
    else if(dataType == 1){
        long long toReturn;
        long long secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(year == mItems.at(i).timeStamp.date().year()){
                    if(mItems.at(i).value == "1"){
                        beforeIs1 = true;
                        timeStart = mItems.at(i).timeStamp;
                    }
                    else if(mItems.at(i).value == "0"){
                        if(beforeIs1){
                            secondElapsed = secondElapsed + (mItems.at(i).timeStamp.toSecsSinceEpoch() - timeStart.toSecsSinceEpoch());
                            beforeIs1 = false;
                            hasValue = true;
                        }
                    }
                }
            }
            if(hasValue){
                if(secondElapsed > 0){
                    toReturn = secondElapsed / 3600;
                }
                else {
                    toReturn = 0;
                }
            }
            else {
                toReturn = 0;
            }
        }
        else {
            toReturn = 0;
        }
        return toReturn;
    }
    else {
        return 0;
    }
}

int PinLogListView::getTodayWeek()
{
    QDate today = QDate::currentDate();
    return today.dayOfWeek();
}

int PinLogListView::getTodayMonth()
{
    QDate today = QDate::currentDate();
    return today.day();
}

int PinLogListView::getMonth()
{
    QDate today = QDate::currentDate();
    return today.month();
}

int PinLogListView::getYear()
{
    QDate today = QDate::currentDate();
    return today.year();
}

int PinLogListView::getDataType() const
{
    return dataType;
}
