#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>

class Notification : public QObject
{
    Q_OBJECT
public:
    explicit Notification(QObject *parent = nullptr);

signals:
    //void notificationSent();
    void sendNotificationSig(int id, QString title, QString body);

public slots:
    void sendNotification(int id, QString title, QString body);
};

#endif // NOTIFICATION_H
