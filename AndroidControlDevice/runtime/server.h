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
    void sentToServer(QVariant jvar);
    void onMessageReceived(QJsonObject json);
    void logOut();
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);

    //check if online or offline
    void isOnline();
    void isOffline();

    //when activity is created
    void initActivity();

    //pong
    void onPong(int elapsedTime, QByteArray payload);
    void onPing(QByteArray payload);
    void onReconnect();

private:
    RemoteReplica *m_remote;
    Connection *m_connection;
    Notification *m_notification;
    QJsonArray m_pinList;
    bool m_isOnline;
    //QVector<QJsonObject> *m_messageQueue;
};

#endif // SERVER_H
