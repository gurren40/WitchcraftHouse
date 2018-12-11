#include "devicecontroller.h"


DeviceController::DeviceController(QObject *parent)
{

}

DeviceController::DeviceController(QSqlDatabase *database, QObject *parent)
{
    this->db = *database;
}

void DeviceController::getDeviceList(QUrl url, QJsonObject json)
{
    DeviceModel model;
    QJsonObject toReturn;
    toReturn = model.getOwnerDevicesList(url.userName());
    sendMessegeToControllDevice(url,toReturn);
}

void DeviceController::setDeviceValue(QUrl url, QJsonObject json)
{

}

void DeviceController::fromWebsocket(QUrl url, QJsonObject json)
{
    switch (json["function"].toString()){
    case "setDeviceValue":
        setDeviceValue(url,json);
        break;
    case "getDeviceList":
        getDeviceList(url,json);
        break;
    }
}

