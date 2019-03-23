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
    void ping(const QString &msg) override;
    //Activity
    void sendToServer(QJsonObject json) override;
    //SIGNAL(fromServerSig(QJsonObject json));
    //Service
    //SIGNAL(sendToServerSig(QJsonObject json));
    void fromServer(QJsonObject json) override;

    //logOut -> to Service
//    SIGNAL(logOutSig());
    void logOut() override;

//    //setIsOnline -> to Activity
//    SIGNAL(setIsOnlineSig(bool isOnline));
    void setIsOnline(bool isOnline) override;

//    //setTokenExpired -> to Activity
//    SIGNAL(tokenExpiredSig(bool isTokenExpired));
    void tokenExpired(bool isTokenExpired) override;
};

#endif // REMOTE_H
