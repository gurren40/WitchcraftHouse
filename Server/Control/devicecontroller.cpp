#include "devicecontroller.h"

DeviceController::DeviceController(QObject *parent) : QObject(parent)
{

}

DeviceController::DeviceController(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

bool DeviceController::isJwtValid(QJsonObject jwt, QString path)
{
    if(path == "/device"){
        if(jwt["iss"].toString() != "WitchcraftHouse") return false;
        User user(&db);
        user.read("email='"+jwt["aud"].toString()+"'");
        if(user.mUsers.size() != 1) return false;
        Device dd(&db);
        dd.read("deviceUUID=UuidToBin('"+jwt["jti"].toString()+"')");
        if(dd.mDevices.size() != 1) return  false;
        //QDateTime dt(dd.mDevices.at(0).expireDate);
        //if(dt.toSecsSinceEpoch() > jwt["exp"].toString().toInt()) return false;
        if(dd.mDevices.at(0).isDeviceOnline) return false;
        if(!toggleDeviceOnline(dd.mDevices.at(0).deviceUUID,true)) return false;
    }
    else {
        return false;
    }
    return  true;
}

bool DeviceController::toggleDeviceOnline(QUuid deviceUUID, bool toggle)
{
    Device devices(&db);
    devices.read("deviceUUID=UuidToBin('"+deviceUUID.toString(QUuid::WithoutBraces)+"')");
    if(devices.mDevices.size() != 1){
        return false;
    }
    if(devices.mDevices.at(0).isDeviceOnline == toggle){
        return false;
    }
    device dvc = devices.mDevices.at(0);
    devices.update(dvc.deviceID,dvc.deviceUUID,dvc.userID,dvc.deviceName,dvc.deviceToken,toggle,dvc.description);
    return true;
}
