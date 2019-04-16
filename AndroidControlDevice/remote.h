#ifndef REMOTE_H
#define REMOTE_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include "rep_remote_source.h"

class Remote : public RemoteSource
{
    //Q_OBJECT

public slots:
    void sendToServer(QVariant jvar) override;
    //SIGNAL(fromServerSig(QVariant jvar));
    //Service
    //SIGNAL(sendToServerSig(QVariant jvar));
    void fromServer(QVariant jvar) override;

    //logOut -> to Service
//    SIGNAL(logOutSig());
    void logOut() override;

//    //setIsOnline -> to Activity
//    SIGNAL(setIsOnlineSig(bool isOnline));
    void setIsOnline(bool isOnline) override;

//    //setTokenExpired -> to Activity
//    SIGNAL(tokenExpiredSig(bool isTokenExpired));
    void tokenExpired(bool isTokenExpired) override;

    void sendToServerVariant(QVariant jvar) override;

    //initActivity -> to Service
    //SIGNAL(initActivitySig());
    void initActivity() override;

    //ping and pong
    //SIGNAL(pingSig(QByteArray payload));
    void ping(QByteArray payload) override;

    //SIGNAL(pongSig(int elapsedTime, QByteArray payload));
    void pong(int elapsedTime, QByteArray payload) override;

    //reconnect
    void reconnect() override;

};

#endif // REMOTE_H
