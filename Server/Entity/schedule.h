#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>
#include <QUuid>

struct schedule{
    int scheduleID;
    int userID;
    QString userName;
    int pinID;
    QUuid pinUUID;
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

class Schedule : public QObject
{
    Q_OBJECT
public:
    explicit Schedule(QObject *parent = nullptr);
    explicit Schedule(QSqlDatabase *database, QObject *parent = nullptr);

    QVector<schedule> mSchedules;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(int userID, int pinID, QString scheduleName, QString minute, QString hour, QString dayOfMonth, QString month, QString dayOfWeek, QString timeZone, QString value, QString description);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int scheduleID, int userID, int pinID, QString scheduleName, QString minute, QString hour, QString dayOfMonth, QString month, QString dayOfWeek, QString timeZone, QString value, QString description);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // SCHEDULE_H
