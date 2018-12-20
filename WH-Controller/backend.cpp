#include "backend.h"

backend::backend(QObject *parent) : QObject(parent)
{

}

void backend::initDevicesValue()
{
    emit getDeviceValueDammnit();
}

void backend::setValue(QString uuid, QString value)
{
    emit setValueDevice(uuid,value);
}

void backend::setWebSocket(QString urlString)
{
    QUrl urlToSend(urlString);
    emit setWebSocketCreate(urlToSend);
}
