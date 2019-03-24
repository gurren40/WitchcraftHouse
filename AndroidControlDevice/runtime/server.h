#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QSignalMapper>

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
    //void tokenExpired();
    //void setIsOnline(); directly connected from m_connection

public slots:
    //THIS IS SERVER DAMNNINT
    void sentToServer(QJsonObject json);
    void onMessageReceived(QJsonObject json);
    void logOut();

private:
    RemoteReplica *m_remote;
    Connection *m_connection;
    Notification *m_notification;
    QJsonArray m_pinList;
};

#endif // SERVER_H
