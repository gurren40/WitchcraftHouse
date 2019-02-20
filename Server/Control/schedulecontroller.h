#ifndef SCHEDULECONTROLLER_H
#define SCHEDULECONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>

class ScheduleController : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleController(QObject *parent = nullptr);
    explicit ScheduleController(QSqlDatabase *database, QObject *parent = nullptr);

signals:

public slots:
    void setDatabase(QSqlDatabase *database);

    //primary function
    //QJsonObject createNewSchedule(QJsonObject json, int userID);
    //QJsonObject editSchedule(QJsonObject json, int userID);
    //QJsonObject deleteSchedule(QJsonObject json, int userID);
    //QJsonObject getScheduleList(int userID, int userID);

private:
    QSqlDatabase db;
};

#endif // SCHEDULECONTROLLER_H
