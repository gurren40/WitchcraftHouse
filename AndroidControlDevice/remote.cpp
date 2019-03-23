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
