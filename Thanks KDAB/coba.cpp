#include "coba.h"

Coba::Coba(QObject *parent) : QObject(parent)
{

}

void Coba::notification(QString msg)
{
    int i = 100;
    jint randomValue = qrand() % i;
    QAndroidJniObject title = QAndroidJniObject::fromString("From server");
    QAndroidJniObject body = QAndroidJniObject::fromString(msg);
    jint keluaran = QAndroidJniObject::callStaticMethod<jint>(m_path.toUtf8(),
                                           "notify",
                                           "(ILjava/lang/String;Ljava/lang/String;)I",
                                           randomValue,
                                           title.object<jstring>(),
                                           body.object<jstring>());
    qDebug() << keluaran;
}

QString Coba::path() const
{
    return m_path;
}

void Coba::setPath(const QString &path)
{
    m_path = path;
}
