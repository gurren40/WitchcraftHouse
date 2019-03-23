#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

public slots:
    void getDeviceList();
    void createNewDevice(QVariant deviceName, QVariant description);
    void editDevice(QVariant deviceID, QVariant deviceUUID, QVariant deviceName, QVariant description);
    void deleteDevice(QVariant deviceID);
    void setPinValue(QVariant UUID, QVariant value);

private:
    RemoteReplica *m_remote;
};

#endif // DEVICE_H
