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

};

#endif // REMOTE_H
