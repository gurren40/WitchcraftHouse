#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>

#include "Entity/schedule.h"

class ScheduleController : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleController(QObject *parent = nullptr);
    explicit ScheduleController(QSqlDatabase *database, QObject *parent = nullptr);

signals:
    void createNewCron(QUuid scheduleUUID, QString cronSyntax, QUuid UUID, QString value, int userID);
    void editCron(QUuid scheduleUUID, QString cronSyntax, QUuid UUID, QString value, int userID);
    void deleteCron(QUuid scheduleUUID);

public slots:
    void setDatabase(QSqlDatabase *database);

    //primary function
    QJsonObject createNewSchedule(QJsonObject json, int userID);
    QJsonObject editSchedule(QJsonObject json, int userID);
    QJsonObject deleteSchedule(QJsonObject json, int userID);
    QJsonObject getScheduleList(int userID);

    //misc
    void initAllCron();
    int getPinIDbyUUID(QUuid UUID);

    //delete! delete!
    void deletedPin(QUuid pinUUID,int userID);

private:
    QSqlDatabase db;
};

#endif // SCHEDULECONTROLLER_H
