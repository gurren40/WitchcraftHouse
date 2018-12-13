#include "devicecontroller.h"
#include <QTextStream>

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
    toReturn = model.getOwnerDevicesList("aditiyasidabutar@student.undip.ac.id");
    sendMessegeToControllDevice(url,toReturn);
    QTextStream(stdout) << url.userName() << '\n';
}

void DeviceController::setDeviceValue(QUrl url, QJsonObject json)
{
    //QUrlQuery theQuery(url.query());
    QUrl urlToSend("http://www.example.com/controll?\
                   username=aditiyasidabutar@student.undip.ac.id\
                   password=qwerty1234" );
    QJsonObject toSend;
    DeviceModel model;
    model.setDatabase(&db);
    bool ok;
    ok = model.setDeviceValue(json["uuid"].toString(),json["value"].toString());
    toSend["function"]="setDeviceValue";
    toSend["uuid"]=json["uuid"].toString();
    toSend["value"]=json["value"].toString();
    if(ok){
        QTextStream(stdout) << "setvalue ok \n";
    }else{
        QTextStream(stdout) << "setvalue error \n";
    }
    emit sendMessegeToControllDevice(urlToSend,toSend);
}

void DeviceController::requestSetDeviceValue(QUrl url, QJsonObject json)
{
    QJsonObject toSend;
    toSend["function"] = QStringLiteral("setValue");
    toSend["uuid"] = json["uuid"].toString();
    toSend["value"] = json["value"].toString();
    QUrl urlToSend("http://www.example.com/device?uuid="+json["uuid"].toString());
    //urlToSend.setUserName(url.userName());
    //urlToSend.setPassword(url.password());
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

