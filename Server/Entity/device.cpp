#include "device.h"

Device::Device(QObject *parent) : QObject(parent)
{

}

Device::Device(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void Device::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject Device::create(QUuid deviceUUID, int userID, QString deviceName, QString deviceToken, bool isDeviceOnline, QString description)
{
    QString textQuery = "INSERT INTO `Device` (`deviceUUID`,`userID`,`deviceName`,`deviceToken`,`isDeviceOnline`,`description`) VALUES (UuidToBin('"+deviceUUID.toString(QUuid::WithoutBraces)+"'),'"+QString::number(userID)+"','"+deviceName+"','"+deviceToken+"','"+QString::number(isDeviceOnline)+"','"+description+"');";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Device::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT UuidFromBin(Device.deviceUUID),Device.deviceID,Device.userID,User.name,Device.deviceName,Device.deviceToken,Device.isDeviceOnline,Device.description FROM Device INNER JOIN User ON Device.userID = User.userID WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mDevices.clear();
            while (query.next()){
                device deviceObject;
                deviceObject.deviceID = query.value("Device.deviceID").toInt();
                deviceObject.deviceUUID = query.value("UuidFromBin(Device.deviceUUID)").toUuid();
                deviceObject.userID = query.value("Device.userID").toInt();
                deviceObject.userName = query.value("User.name").toString();
                deviceObject.deviceName = query.value("Device.deviceName").toString();
                deviceObject.deviceToken = query.value("Device.deviceToken").toString();
                deviceObject.isDeviceOnline = query.value("Device.isDeviceOnline").toBool();
                deviceObject.description = query.value("Device.description").toString();
                mDevices.append(deviceObject);
            }
            mDevices.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Device::update(int deviceID, QUuid deviceUUID, int userID, QString deviceName, QString deviceToken, bool isDeviceOnline, QString description)
{
    QString textQuery = "UPDATE `Device` SET deviceUUID=UuidToBin('"+deviceUUID.toString(QUuid::WithoutBraces)+"'),userID='"+QString::number(userID)+"',deviceName='"+deviceName+"',deviceToken='"+deviceToken+"',isDeviceOnline='"+QString::number(isDeviceOnline)+"',description='"+description+"' WHERE deviceID='"+QString::number(deviceID)+"';";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Device::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `Device` WHERE "+wherequery+";";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}
