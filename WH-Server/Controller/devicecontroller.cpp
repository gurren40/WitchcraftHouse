#include "devicecontroller.h"

DeviceController::DeviceController(QObject *parent) : QObject(parent)
{

}

void DeviceController::setDeviceValue(QJsonObject json)
{
    DeviceModel the_model(json["uuid"].toString());
    the_model.setValue(json["value"].toString());
    the_model.deleteLater();
}
