#include <QCoreApplication>
#include <QSqlDatabase>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QTextStream>

//Entitiy
#include "Entity/user.h"
#include "Entity/icon.h"
#include "Entity/pintype.h"
#include "Entity/group.h"
#include "Entity/device.h"

//Boundary
#include "Boundary/websocketserver.h"

//Controller
#include "Control/usercontroller.h"

static QSqlDatabase setDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("witchcraft");
    db.setUserName("admin");
    db.setPassword("azsx312");
    db.setPort(3306);
    bool ok = db.open();
    if (ok){
        return db;
    } else {
        QTextStream(stdout) << "ERROR: "+ db.lastError().text() + "\n";
        return db;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //>percobaan
    QJsonObject json;
    QSqlDatabase db = setDatabase();

    int i;
    QString data;

    Device obj(&db);
    //user.setDatabase(&db);
    json = obj.create(6,"Jackson","sometokenhereasdrfawfa34wefva34",0,"inideskripsinya");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    for (i=0;i<obj.mDevices.size();i++) {
        data += "deviceID : "+QString::number(obj.mDevices.at(i).deviceID)+", ";
        data += "userID : "+QString::number(obj.mDevices.at(i).userID)+", ";
        data += "userName : "+obj.mDevices.at(i).userName+", ";
        data += "deviceName : "+obj.mDevices.at(i).deviceName+", ";
        data += "deviceToken : "+obj.mDevices.at(i).deviceToken+", ";
        data += "isDeviceOnline : "+QString::number(obj.mDevices.at(i).isDeviceOnline)+", ";
        data += "description : "+obj.mDevices.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    json = obj.update(1,8,"Thunder","sdafasefasdfaeasdfa",1,"sedikitdeskripsi");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.deletes("deviceID='3'");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    data = "";
    for (i=0;i<obj.mDevices.size();i++) {
        data += "deviceID : "+QString::number(obj.mDevices.at(i).deviceID)+", ";
        data += "userID : "+QString::number(obj.mDevices.at(i).userID)+", ";
        data += "userName : "+obj.mDevices.at(i).userName+", ";
        data += "deviceName : "+obj.mDevices.at(i).deviceName+", ";
        data += "deviceToken : "+obj.mDevices.at(i).deviceToken+", ";
        data += "isDeviceOnline : "+QString::number(obj.mDevices.at(i).isDeviceOnline)+", ";
        data += "description : "+obj.mDevices.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    //<percobaan

    return a.exec();
}
