#ifndef SCHEDULELIST_H
#define SCHEDULELIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

struct ScheduleItem
{
    //bool done;
    //QString description;
    int scheduleID;
    QString scheduleUUID;
    int userID;
    QString userName;
    int pinID;
    QString pinUUID;
    QString pinName;
    QString scheduleName;
    QString minute;
    QString hour;
    QString dayOfMonth;
    QString month;
    QString dayOfWeek;
    QString timeZone;
    QString value;
    QString description;
};

class ScheduleList : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleList(QObject *parent = nullptr);

    QVector<ScheduleItem> items() const;

    bool setItemAt(int index, const ScheduleItem &item);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setScheduleList(QJsonObject json);

private:
    QVector<ScheduleItem> mItems;
};

#endif // PINLIST_H
