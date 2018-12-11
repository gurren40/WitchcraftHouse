#include "backend.h"

backend::backend(QObject *parent) : QObject(parent)
{

}

void backend::initDevicesValue()
{
    emit getDeviceValueDammnit();
}
