#include "service.h"

Service::Service(QObject *parent) : ServiceSource(parent)
{

}

void Service::ping(const QString &msg)
{
    emit pong(msg + " from server");
    QTextStream(stdout) << msg << " from server";
    qDebug() << msg << " from server";
}
