#include "remote.h"
#include "services/notification.h"

void Remote::sendToServer(QVariant jvar)
{
    emit sendToServerSig(jvar);
}

void Remote::fromServer(QVariant jvar)
{
    emit fromServerSig(jvar);
}

void Remote::logOut()
{
    emit logOutSig();
}

void Remote::setIsOnline(bool isOnline)
{
    emit setIsOnlineSig(isOnline);
}

void Remote::tokenExpired(bool isTokenExpired)
{
    emit tokenExpiredSig(isTokenExpired);
}

void Remote::sendToServerVariant(QVariant jvar)
{
    emit sendToServerVariantSig(jvar);
}

void Remote::initActivity()
{
    emit initActivitySig();
}

void Remote::ping(QByteArray payload)
{
    //ping and pong
    emit pingSig(payload);
}

void Remote::pong(int elapsedTime, QByteArray payload)
{
    emit pongSig(elapsedTime,payload);
}

void Remote::reconnect()
{
    emit reconnectSig();
}
