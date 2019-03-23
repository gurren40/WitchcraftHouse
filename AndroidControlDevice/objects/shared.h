#ifndef SHARED_H
#define SHARED_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

class Shared : public QObject
{
    Q_OBJECT
public:
    explicit Shared(QObject *parent = nullptr);

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

public slots:
    void getSharedList();
    void createNewShared(QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
    void editShared(QVariant sharedID, QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
    void deleteShared(QVariant sharedID);

private:
    RemoteReplica *m_remote;
};

#endif // SHARED_H
