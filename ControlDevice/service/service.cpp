#include "service.h"

void Service::ping(const QString &msg)
{
    emit pong(msg + " from server");
    QTextStream(stdout) << msg << " from server";
}
