#include "notification.h"

Notification::Notification(QObject *parent) : QObject(parent)
{

}

void Notification::sendNotification(int id, QString title, QString body)
{
    emit sendNotificationSig(id, title, body);
}
