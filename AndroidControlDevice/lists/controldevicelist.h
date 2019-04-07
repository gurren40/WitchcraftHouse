#ifndef CONTROLDEVICELIST_H
#define CONTROLDEVICELIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include <QSettings>
#include "rep_remote_replica.h"

struct ControlDeviceItem
{
    //bool done;
    //QString description;
    QString controlDeviceID;
    int userID;
    QString userName;
    QString controlDeviceName;
    QString controlDeviceToken;
    bool isControlDeviceOnline;
    QDate expireDate;
};

class ControlDeviceList : public QObject
{
    Q_OBJECT
public:
    explicit ControlDeviceList(QObject *parent = nullptr);

    QVector<ControlDeviceItem> items() const;

    bool setItemAt(int index, const ControlDeviceItem &item);

    RemoteReplica *getRemote() const;
    void setRemote(RemoteReplica *remote);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();
    void preItemDataChanged();
    void postItemDataChanged();

public slots:
    void setControlDeviceList(QJsonObject json);
    void getControlDeviceList();
    void deleteControlDevice(QVariant controlDeviceID);

    //misc
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);

private:
    QVector<ControlDeviceItem> mItems;
    RemoteReplica *m_remote;
};

#endif // CONTROLDEVICELIST_H
