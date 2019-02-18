#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>
#include <QUuid>

struct device{
    int deviceID;
    QUuid deviceUUID;
    int userID;
    QString userName;
    QString deviceName;
    QString deviceToken;
    bool isDeviceOnline;
    QString description;
};

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);
    explicit Device(QSqlDatabase *database,QObject *parent = nullptr);

    QVector<device> mDevices;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(QUuid deviceUUID, int userID, QString deviceName, QString deviceToken, bool isDeviceOnline, QString description);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int deviceID, QUuid deviceUUID, int userID, QString deviceName, QString deviceToken, bool isDeviceOnline, QString description);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // DEVICE_H
