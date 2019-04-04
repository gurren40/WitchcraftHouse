#ifndef SCHEDULELIST_H
#define SCHEDULELIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

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
    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setScheduleList(QJsonObject json);
    void getScheduleList();
    void createNewSchedule(QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
    void editSchedule(QVariant scheduleID, QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
    void deleteSchedule(QVariant scheduleID);

    //misc
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);

private:
    QVector<ScheduleItem> mItems;
    RemoteReplica *m_remote;
};

#endif // SCHEDULELIST_H
