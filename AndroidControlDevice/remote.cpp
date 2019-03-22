#include "remote.h"

void Remote::ping(const QString &msg){
    qDebug() << msg;
    qDebug() << "selamatkah sampai disini?";
    emit pong(msg + " from server");
}
