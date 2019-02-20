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
    void setDatabase(QSqlDatabase *database);
    bool isJwtValid(QJsonObject jwt, QString path);
    bool toggleDeviceOnline(QUuid deviceUUID, bool toggle);

    //primary function
    //create
    //QJsonObject createNewDevice(QJsonObject json, int userID);
    //QJsonObject createNewGroup(QJsonObject json, int userID);
    //QJsonObject createNewPin(QJsonObject json, int userID);

    //edit
    //QJsonObject editDevice(QJsonObject json, int userID);
    //QJsonObject editGroup(QJsonObject json, int userID);
    //QJsonObject editPin(QJsonObject json, int userID);

    //delete
    //QJsonObject deleteDevice(QJsonObject json, int userID);
    //QJsonObject deleteGroup(QJsonObject json, int userID);
    //QJsonObject deletePin(QJsonObject json, int userID);

    //get list
    //QJsonObject getDeviceList(int userID);
    //QJsonObject getGroupList(int userID);
    //QJsonObject getPinList(QJsonObject userID);

    //set device value
    //QJsonObject setPinValue(QJsonObject json);
    //QJsonObject settedPinValue(QJsonObject json);


private:
    QSqlDatabase db;
};

#endif // DEVICECONTROLLER_H
