#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

class Schedule : public QObject
{
    Q_OBJECT
public:
    explicit Schedule(QObject *parent = nullptr);

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

public slots:
    void getScheduleList();
    void createNewSchedule(QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
    void editSchedule(QVariant scheduleID, QVariant scheduleName, QVariant pinUUID, QVariant minute, QVariant hour, QVariant dayOfMonth, QVariant month, QVariant dayOfWeek, QVariant timeZone, QVariant value, QVariant description);
    void deleteSchedule(QVariant scheduleID);

private:
    RemoteReplica *m_remote;
};

#endif // SCHEDULE_H
