#include "controlldevice.h"

ControllDevice::ControllDevice(QObject *parent) : QObject(parent)
{

}

ControllDevice::ControllDevice(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void ControllDevice::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject ControllDevice::create(QUuid controlDeviceID, int userID, QString controlDeviceName, QString controlDeviceToken, bool isControlDeviceOnline, QDate expireDate)
{
    QString textQuery = "INSERT INTO `ControlDevice` (`controlDeviceID`,`userID`,`ControlDeviceName`,`ControlDeviceToken`,`isControlDeviceOnline`,`expireDate`) VALUES (UuidToBin('"+controlDeviceID.toString(QUuid::WithoutBraces)+"'),'"+QString::number(userID)+"','"+controlDeviceName+"','"+controlDeviceToken+"','"+QString::number(isControlDeviceOnline)+"','"+expireDate.toString("yyyy-MM-dd")+"');";
    QSqlQuery query; //(,
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

QJsonObject ControllDevice::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT UuidFromBin(ControlDevice.controlDeviceID),ControlDevice.userID,User.name,ControlDevice.controlDeviceName,ControlDevice.controlDeviceToken,ControlDevice.isControlDeviceOnline,ControlDevice.expireDate FROM ControlDevice INNER JOIN User ON ControlDevice.userID = User.userID WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mControlDevices.clear();
            while (query.next()){
                controlDevice controlDeviceObject;
                controlDeviceObject.controlDeviceID = query.value("UuidFromBin(ControlDevice.controlDeviceID)").toUuid();
                controlDeviceObject.userID = query.value("ControlDevice.userID").toInt();
                controlDeviceObject.userName = query.value("User.name").toString();
                controlDeviceObject.controlDeviceName = query.value("ControlDevice.controlDeviceName").toString();
                controlDeviceObject.controlDeviceToken = query.value("ControlDevice.controlDeviceToken").toString();
                controlDeviceObject.isControlDeviceOnline = query.value("ControlDevice.isControlDeviceOnline").toBool();
                controlDeviceObject.expireDate = query.value("ControlDevice.expireDate").toDate();
                mControlDevices.append(controlDeviceObject);
            }
            mControlDevices.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject ControllDevice::update(QUuid controlDeviceID, int userID, QString controlDeviceName, QString controlDeviceToken, bool isControlDeviceOnline, QDate expireDate)
{
    QString textQuery = "UPDATE `ControlDevice` SET `userID`='"+QString::number(userID)+"',`ControlDeviceName`='"+controlDeviceName+"',`ControlDeviceToken`='"+controlDeviceToken+"',`isControlDeviceOnline`='"+QString::number(isControlDeviceOnline)+"',`expireDate`='"+expireDate.toString("yyyy-MM-dd")+"' WHERE controlDeviceID=UuidToBin('"+controlDeviceID.toString(QUuid::WithoutBraces)+"')";
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

QJsonObject ControllDevice::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `ControlDevice` WHERE "+wherequery+";";
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
