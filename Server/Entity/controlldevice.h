#ifndef CONTROLLDEVICE_H
#define CONTROLLDEVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>
#include <QDate>
#include <QUuid>

struct controlDevice{
    QUuid controlDeviceID;
    int userID;
    QString userName;
    QString controlDeviceName;
    QString controlDeviceToken;
    bool isControlDeviceOnline;
    QDate expireDate;
};

class ControllDevice : public QObject
{
    Q_OBJECT
public:
    explicit ControllDevice(QObject *parent = nullptr);
    explicit ControllDevice(QSqlDatabase *database,QObject *parent = nullptr);

    QVector<controlDevice> mControlDevices;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(QUuid controlDeviceID, int userID, QString controlDeviceName, QString controlDeviceToken, bool isControlDeviceOnline, QDate expireDate);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(QUuid controlDeviceID, int userID, QString controlDeviceName, QString controlDeviceToken, bool isControlDeviceOnline, QDate expireDate);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // CONTROLLDEVICE_H
