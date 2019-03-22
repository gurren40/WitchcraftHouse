#include "notification.h"
#include <QAndroidJniObject>

Notification::Notification(QObject *parent) : QObject(parent)
{

}

Notification::Notification(QString javaClass, QObject *parent) : QObject(parent)
{
    m_javaClass = javaClass;
}

QString Notification::javaClass() const
{
    return m_javaClass;
}

void Notification::setJavaClass(const QString &javaClass)
{
    m_javaClass = javaClass;
}

void Notification::sendNotification(int id, QString title, QString body)
{
    jint jNotificationID = id;
    QAndroidJniObject jNotificationTitle = QAndroidJniObject::fromString(title);
    QAndroidJniObject jNotificationText = QAndroidJniObject::fromString(body);
    QAndroidJniObject::callStaticMethod<void>(m_javaClass.toUtf8(),
                                       "notify",
                                       "(ILjava/lang/String;Ljava/lang/String;)V",
                                       jNotificationID,
                                       jNotificationTitle.object<jstring>(),
                                       jNotificationText.object<jstring>());
}

void Notification::notify(QString body)
{
    int id = qrand() % 100;
    sendNotification(id,"From Service",body);
}
