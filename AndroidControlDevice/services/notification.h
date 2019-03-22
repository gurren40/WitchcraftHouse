#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>

class Notification : public QObject
{
    Q_OBJECT
public:
    explicit Notification(QObject *parent = nullptr);
    explicit Notification(QString javaClass, QObject *parent = nullptr);

    QString javaClass() const;
    void setJavaClass(const QString &javaClass);

signals:
    void notificationSent();

public slots:
    void sendNotification(int id, QString title, QString body);
    void notify(QString body);

private:
    QString m_javaClass;
};

#endif // NOTIFICATION_H
