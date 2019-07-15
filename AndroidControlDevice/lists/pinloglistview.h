#ifndef PINLOGLISTVIEW_H
#define PINLOGLISTVIEW_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QDateTime>
#include <QUuid>
#include "logstructs.h"

class PinLogListView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int datatype READ getDataType WRITE setDataType)
    Q_PROPERTY(int dayWeek READ getTodayWeek)
    Q_PROPERTY(int dayMonth READ getTodayMonth)
    Q_PROPERTY(int month READ getMonth)
    Q_PROPERTY(int year READ getYear)

public:
    explicit PinLogListView(QObject *parent = nullptr);

    QVector<pinLogItem> items() const;

    void setPinLogItems(const QVector<pinLogItem> &pinLogItems);
    bool setItemAt(int index, const pinLogItem &item);

    void setDataType(int value);

    int getDataType() const;

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemDataChanged();
    void postItemDataChanged();

    void itemDataChanged(int first, int last);

public slots:
    //setter to own list
    QVariant readDayWeek(int day); //(1 = monday, 7 = sunday)
    QVariant readDayMonth(int day); //(day 1 to 31)
    QVariant readMonth(int month); //(1 = jan, 12 =  dec)
    QVariant readYear(int year);

    int getTodayWeek();
    int getTodayMonth();
    int getMonth();
    int getYear();

private:
    QVector<pinLogItem> mItems;
    int dataType; //0=mean//1=hours used
};

#endif // PINLOGLIST_H
