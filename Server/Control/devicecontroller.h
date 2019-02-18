#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QJsonObject>

#include "Entity/device.h"
#include "Entity/user.h"

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    explicit DeviceController(QSqlDatabase *database, QObject *parent = nullptr);

signals:

public slots:
    bool isJwtValid(QJsonObject jwt, QString path);
    bool toggleDeviceOnline(QUuid deviceUUID, bool toggle);

private:
    QSqlDatabase db;
};

#endif // DEVICECONTROLLER_H
