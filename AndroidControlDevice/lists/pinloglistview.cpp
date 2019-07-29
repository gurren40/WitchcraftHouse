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
        float toReturn;
        float secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(day == mItems.at(i).timeStamp.date().dayOfWeek()){
                    if(mItems.at(i).value == "1"){
                        if(!beforeIs1){
                            beforeIs1 = true;
                            timeStart = mItems.at(i).timeStamp;
                        }
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
        float toReturn;
        float secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(day == mItems.at(i).timeStamp.date().day()){
                    if(mItems.at(i).value == "1"){
                        if(!beforeIs1){
                            beforeIs1 = true;
                            timeStart = mItems.at(i).timeStamp;
                        }
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
        float toReturn;
        float secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(month == mItems.at(i).timeStamp.date().month()){
                    if(mItems.at(i).value == "1"){
                        if(!beforeIs1){
                            beforeIs1 = true;
                            timeStart = mItems.at(i).timeStamp;
                        }
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
        float toReturn;
        float secondElapsed = 0;
        QDateTime timeStart;
        bool beforeIs1 = false;
        bool hasValue = false;
        if(mItems.size()>0){
            for (int i = 0;i < mItems.size();i++) {
                if(year == mItems.at(i).timeStamp.date().year()){
                    if(mItems.at(i).value == "1"){
                        if(!beforeIs1){
                            beforeIs1 = true;
                            timeStart = mItems.at(i).timeStamp;
                        }
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

QVariant PinLogListView::thisMonth()
{
    return readMonth(getMonth());
}

QVariant PinLogListView::thisYear()
{
    return year1();
}

QVariant PinLogListView::dw1()
{
    return readDayWeek(1);
}
QVariant PinLogListView::dw2()
{
    return readDayWeek(2);
}
QVariant PinLogListView::dw3()
{
    return readDayWeek(3);
}
QVariant PinLogListView::dw4()
{
    return readDayWeek(4);
}
QVariant PinLogListView::dw5()
{
    return readDayWeek(5);
}
QVariant PinLogListView::dw6()
{
    return readDayWeek(6);
}
QVariant PinLogListView::dw7()
{
    return readDayWeek(7);
}

QVariant PinLogListView::dm1()
{
    return readDayMonth(1);
}
QVariant PinLogListView::dm2()
{
    return readDayMonth(2);
}
QVariant PinLogListView::dm3()
{
    return readDayMonth(3);
}
QVariant PinLogListView::dm4()
{
    return readDayMonth(4);
}
QVariant PinLogListView::dm5()
{
    return readDayMonth(5);
}
QVariant PinLogListView::dm6()
{
    return readDayMonth(6);
}
QVariant PinLogListView::dm7()
{
    return readDayMonth(7);
}
QVariant PinLogListView::dm8()
{
    return readDayMonth(8);
}
QVariant PinLogListView::dm9()
{
    return readDayMonth(9);
}
QVariant PinLogListView::dm10()
{
    return readDayMonth(10);
}
QVariant PinLogListView::dm11()
{
    return readDayMonth(11);
}
QVariant PinLogListView::dm12()
{
    return readDayMonth(12);
}
QVariant PinLogListView::dm13()
{
    return readDayMonth(13);
}
QVariant PinLogListView::dm14()
{
    return readDayMonth(14);
}
QVariant PinLogListView::dm15()
{
    return readDayMonth(15);
}
QVariant PinLogListView::dm16()
{
    return readDayMonth(16);
}
QVariant PinLogListView::dm17()
{
    return readDayMonth(17);
}
QVariant PinLogListView::dm18()
{
    return readDayMonth(18);
}
QVariant PinLogListView::dm19()
{
    return readDayMonth(19);
}
QVariant PinLogListView::dm20()
{
    return readDayMonth(20);
}
QVariant PinLogListView::dm21()
{
    return readDayMonth(21);
}
QVariant PinLogListView::dm22()
{
    return readDayMonth(22);
}
QVariant PinLogListView::dm23()
{
    return readDayMonth(23);
}
QVariant PinLogListView::dm24()
{
    return readDayMonth(24);
}
QVariant PinLogListView::dm25()
{
    return readDayMonth(25);
}
QVariant PinLogListView::dm26()
{
    return readDayMonth(26);
}
QVariant PinLogListView::dm27()
{
    return readDayMonth(27);
}
QVariant PinLogListView::dm28()
{
    return readDayMonth(28);
}
QVariant PinLogListView::dm29()
{
    return readDayMonth(29);
}
QVariant PinLogListView::dm30()
{
    return readDayMonth(30);
}
QVariant PinLogListView::dm31()
{
    return readDayMonth(31);
}

QVariant PinLogListView::month1()
{
    return readMonth(1);
}
QVariant PinLogListView::month2()
{
    return readMonth(2);
}
QVariant PinLogListView::month3()
{
    return readMonth(3);
}
QVariant PinLogListView::month4()
{
    return readMonth(4);
}
QVariant PinLogListView::month5()
{
    return readMonth(5);
}
QVariant PinLogListView::month6()
{
    return readMonth(6);
}
QVariant PinLogListView::month7()
{
    return readMonth(7);
}
QVariant PinLogListView::month8()
{
    return readMonth(8);
}
QVariant PinLogListView::month9()
{
    return readMonth(9);
}
QVariant PinLogListView::month10()
{
    return readMonth(10);
}
QVariant PinLogListView::month11()
{
    return readMonth(11);
}
QVariant PinLogListView::month12()
{
    return readMonth(12);
}

QVariant PinLogListView::year1()
{
    return readYear(getYear());
}

int PinLogListView::getDataType() const
{
    return dataType;
}
