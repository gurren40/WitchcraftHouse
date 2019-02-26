#ifndef CRONSCHEDULER_H
#define CRONSCHEDULER_H

#include <QObject>
#include <QHash>
#include <QUuid>
#include <QJsonArray>
#include <QJsonObject>

#include "Library/qcron-master/src/qcron.hpp"

struct setPin{
    QUuid UUID;
    QString value;
    int userID;
};

class CronScheduler : public QObject
{
    Q_OBJECT
public:

    QHash<QUuid,QCron*> mCronList;
    QHash<QUuid,setPin> mPinList;
    explicit CronScheduler(QObject *parent = nullptr);

signals:

    void setPinValue(QJsonObject json, int userID);

public slots:

    void onSignalEmitted();
    void createNewCron(QUuid scheduleUUID, QString cronSyntax, QUuid UUID, QString value, int userID);
    void editCron(QUuid scheduleUUID, QString cronSyntax, QUuid UUID, QString value, int userID);
    void deleteCron(QUuid scheduleUUID);
};

#endif // CRONSCHEDULER_H
