#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>

#include "services/connection.h"
#include "services/notification.h"
#include "rep_remote_replica.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

public slots:
    //THIS IS SERVER DAMNNINT
    void sendToServer(QJsonObject json);

private:
    RemoteReplica *m_remote;
};

#endif // SERVER_H
