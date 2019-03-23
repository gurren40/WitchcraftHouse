#include "remote.h"
#include "services/notification.h"

void Remote::ping(const QString &msg){
    qDebug() << msg;
    qDebug() << "selamatkah sampai disini?";
    emit pong(msg + " from server");
    Notification notify;
    notify.setJavaClass("id/web/witchcraft/house/MyService");
    notify.notify(msg);
}

void Remote::sendToServer(QJsonObject json)
{
    emit sendToServerSig(json);
}

void Remote::fromServer(QJsonObject json)
{
    emit fromServerSig(json);
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
