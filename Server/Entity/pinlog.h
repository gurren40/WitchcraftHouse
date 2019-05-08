#ifndef PINLOG_H
#define PINLOG_H

#include <QObject>
#include <QDateTime>
#include <QVector>
#include <QSqlDatabase>
#include <QUuid>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlQuery>
#include <QTextStream>
#include <QSqlError>

struct pinLog{
    int pinLogID;
    int userID;
    QString userName;
    int pinID;
    QString pinName;
    QUuid pinUUID;
    int pinTypeID;
    QString pinTypeName;
    QString value;
    QString description;
    QDateTime timeStamp;
};

class PinLog : public QObject
{
    Q_OBJECT
public:
    explicit PinLog(QObject *parent = nullptr);
    explicit PinLog(QSqlDatabase *database, QObject *parent = nullptr);
    QVector<pinLog> mPinLog;

signals:

public slots:
    void setDatabase(QSqlDatabase *database);

    QJsonObject create(int userID, int pinID, QString value, QString description);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int pinLogID,int userID, int pinID, QString value, QString description);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // PINLOG_H
