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

    //present
    Q_PROPERTY(QVariant thisMonth READ thisMonth NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant thisYear READ thisYear NOTIFY postItemDataChanged)

    //day of week
    Q_PROPERTY(QVariant dw1 READ dw1 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dw2 READ dw2 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dw3 READ dw3 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dw4 READ dw4 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dw5 READ dw5 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dw6 READ dw6 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dw7 READ dw7 NOTIFY postItemDataChanged)

    //day of month
    Q_PROPERTY(QVariant dm1 READ dm1 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm2 READ dm2 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm3 READ dm3 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm4 READ dm4 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm5 READ dm5 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm6 READ dm6 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm7 READ dm7 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm8 READ dm8 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm9 READ dm9 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm10 READ dm10 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm11 READ dm11 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm12 READ dm12 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm13 READ dm13 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm14 READ dm14 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm15 READ dm15 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm16 READ dm16 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm17 READ dm17 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm18 READ dm18 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm19 READ dm19 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm20 READ dm20 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm21 READ dm21 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm22 READ dm22 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm23 READ dm23 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm24 READ dm24 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm25 READ dm25 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm26 READ dm26 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm27 READ dm27 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm28 READ dm28 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm29 READ dm29 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm30 READ dm30 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant dm31 READ dm31 NOTIFY postItemDataChanged)

    //month
    Q_PROPERTY(QVariant month1 READ month1 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month2 READ month2 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month3 READ month3 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month4 READ month4 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month5 READ month5 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month6 READ month6 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month7 READ month7 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month8 READ month8 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month9 READ month9 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month10 READ month10 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month11 READ month11 NOTIFY postItemDataChanged)
    Q_PROPERTY(QVariant month12 READ month12 NOTIFY postItemDataChanged)

    //year
    Q_PROPERTY(QVariant year1 READ year1 NOTIFY postItemDataChanged)

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

    //present
    QVariant thisMonth();
    QVariant thisYear();

    //fkin day of week
    QVariant dw1();
    QVariant dw2();
    QVariant dw3();
    QVariant dw4();
    QVariant dw5();
    QVariant dw6();
    QVariant dw7();

    //day of month
    QVariant dm1();
    QVariant dm2();
    QVariant dm3();
    QVariant dm4();
    QVariant dm5();
    QVariant dm6();
    QVariant dm7();
    QVariant dm8();
    QVariant dm9();
    QVariant dm10();
    QVariant dm11();
    QVariant dm12();
    QVariant dm13();
    QVariant dm14();
    QVariant dm15();
    QVariant dm16();
    QVariant dm17();
    QVariant dm18();
    QVariant dm19();
    QVariant dm20();
    QVariant dm21();
    QVariant dm22();
    QVariant dm23();
    QVariant dm24();
    QVariant dm25();
    QVariant dm26();
    QVariant dm27();
    QVariant dm28();
    QVariant dm29();
    QVariant dm30();
    QVariant dm31();

    //month
    QVariant month1();
    QVariant month2();
    QVariant month3();
    QVariant month4();
    QVariant month5();
    QVariant month6();
    QVariant month7();
    QVariant month8();
    QVariant month9();
    QVariant month10();
    QVariant month11();
    QVariant month12();

    //year
    QVariant year1();

private:
    QVector<pinLogItem> mItems;
    int dataType; //0=mean//1=hours used
};

#endif // PINLOGLIST_H
