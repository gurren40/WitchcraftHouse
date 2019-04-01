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
