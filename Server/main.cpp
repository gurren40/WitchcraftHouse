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
#include "Entity/controlldevice.h"
#include "Entity/pin.h"

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

    Pin obj(&db);
    //user.setDatabase(&db);
    json = obj.create(QUuid().createUuid(),21,2,4,3,1,"Colokan Wifi","off","on,off","hanya sedikit deskripsi disini byee");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    for (i=0;i<obj.mPins.size();i++) {
        data += "pinID : "+QString::number(obj.mPins.at(i).pinID)+", ";
        data += "UUID : "+obj.mPins.at(i).UUID.toString(QUuid::WithoutBraces)+", ";
        data += "userID : "+QString::number(obj.mPins.at(i).userID)+", ";
        data += "userName : "+obj.mPins.at(i).userName+", ";
        data += "groupID : "+QString::number(obj.mPins.at(i).groupID)+", ";
        data += "groupName : "+obj.mPins.at(i).groupName+", ";
        data += "deviceID : "+QString::number(obj.mPins.at(i).deviceID)+", ";
        data += "deviceName : "+obj.mPins.at(i).deviceName+", ";
        data += "iconID : "+QString::number(obj.mPins.at(i).iconID)+", ";
        data += "iconName : "+obj.mPins.at(i).iconName+", ";
        data += "pinTypeID : "+QString::number(obj.mPins.at(i).pinTypeID)+", ";
        data += "pinTypeName : "+obj.mPins.at(i).pinTypeName+", ";
        data += "pinName : "+obj.mPins.at(i).pinName+", ";
        data += "value : "+obj.mPins.at(i).value+", ";
        data += "option : "+obj.mPins.at(i).option+", ";
        data += "expireDate : "+obj.mPins.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    json = obj.update(1,QUuid().createUuid(),21,2,4,3,1,"Colokan Wifi","off","on,off","hanya sedikit deskripsi disini byee");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.deletes("pinID='4'");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    data = "";
    for (i=0;i<obj.mPins.size();i++) {
        data += "pinID : "+QString::number(obj.mPins.at(i).pinID)+", ";
        data += "UUID : "+obj.mPins.at(i).UUID.toString(QUuid::WithoutBraces)+", ";
        data += "userID : "+QString::number(obj.mPins.at(i).userID)+", ";
        data += "userName : "+obj.mPins.at(i).userName+", ";
        data += "groupID : "+QString::number(obj.mPins.at(i).groupID)+", ";
        data += "groupName : "+obj.mPins.at(i).groupName+", ";
        data += "deviceID : "+QString::number(obj.mPins.at(i).deviceID)+", ";
        data += "deviceName : "+obj.mPins.at(i).deviceName+", ";
        data += "iconID : "+QString::number(obj.mPins.at(i).iconID)+", ";
        data += "iconName : "+obj.mPins.at(i).iconName+", ";
        data += "pinTypeID : "+QString::number(obj.mPins.at(i).pinTypeID)+", ";
        data += "pinTypeName : "+obj.mPins.at(i).pinTypeName+", ";
        data += "pinName : "+obj.mPins.at(i).pinName+", ";
        data += "value : "+obj.mPins.at(i).value+", ";
        data += "option : "+obj.mPins.at(i).option+", ";
        data += "expireDate : "+obj.mPins.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    //<percobaan

    return a.exec();
}
