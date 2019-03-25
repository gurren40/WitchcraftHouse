#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

struct DeviceItem
{
    //bool done;
    //QString description;
    int deviceID;
    QString deviceUUID;
    int userID;
    QString userName;
    QString deviceName;
    QString deviceToken;
    bool isDeviceOnline;
    QString description;
};

class DeviceList : public QObject
{
    Q_OBJECT
public:
    explicit DeviceList(QObject *parent = nullptr);

    QVector<DeviceItem> items() const;

    bool setItemAt(int index, const DeviceItem &item);

    //remote object
    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setDeviceList(QJsonObject json);
    void getDeviceList();
    void createNewDevice(QVariant deviceName, QVariant description);
    void editDevice(QVariant deviceID, QVariant deviceUUID, QVariant deviceName, QVariant description);
    void deleteDevice(QVariant deviceID);
    void setPinValue(QVariant UUID, QVariant value);

private:
    QVector<DeviceItem> mItems;
    RemoteReplica *m_remote;
};

#endif // TODOLIST_H
