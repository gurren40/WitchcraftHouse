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
    model.setDatabase(&db);
    QJsonObject toReturn;
    toReturn = model.getOwnerDevicesList(url.userName());
    sendMessegeToControllDevice(url,toReturn);
}

void DeviceController::setDeviceValue(QUrl url, QJsonObject json)
{
    QUrl urlToSend("http://www.example.com/controll");
    QJsonObject toSend;
    DeviceModel model;
    model.setDeviceValue(json["uuid"].toString(),json["value"].toString());
    toSend["uuid"]=json["uuid"].toString();
    toSend["value"]=json["value"].toString();
    urlToSend.setUserName(url.userName());
    urlToSend.setPassword(url.password());
    emit sendMessegeToControllDevice(urlToSend,toSend);
}

void DeviceController::requestSetDeviceValue(QUrl url, QJsonObject json)
{
    QJsonObject toSend;
    toSend["function"] = QStringLiteral("setValue");
    toSend["uuid"] = json["uuid"].toString();
    toSend["value"] = json["value"].toString();
    QUrl urlToSend("http://www.example.com/device/"+json["uuid"].toString());
    urlToSend.setUserName(url.userName());
    urlToSend.setPassword(url.password());
    emit sendMessegeToDevice(json["uuid"].toString(),urlToSend,toSend);
}

void DeviceController::fromWebsocket(QUrl url, QJsonObject json)
{
    if (json["function"].toString() == "setDeviceValue"){
        setDeviceValue(url,json);
    } else if (json["function"].toString() == "getDeviceList"){
        getDeviceList(url,json);
    } else if (json["function"].toString() == "requestSetDeviceValue"){
        requestSetDeviceValue(url,json);
    }
}

