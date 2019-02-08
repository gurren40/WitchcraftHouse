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
#include "Entity/schedule.h"
#include "Entity/shared.h"
#include "Entity/log.h"

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

    Log obj(&db);
    //user.setDatabase(&db);
    json = obj.create(8,"Wkwkwkwkwk");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    for (i=0;i<obj.mLogs.size();i++) {
        data += "logID : "+QString::number(obj.mLogs.at(i).logID)+", ";
        data += "userID : "+QString::number(obj.mLogs.at(i).userID)+", ";
        data += "timeStamp : "+obj.mLogs.at(i).timeStamp.toString("yyyy-MM-dd HH:mm:ss")+", ";
        data += "timeStamp (UTC): "+obj.mLogs.at(i).timeStamp.toUTC().toString("yyyy-MM-dd HH:mm:ss")+", ";
        data += "description : "+obj.mLogs.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    json = obj.update(2,21,"LALALALALA");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.deletes("logID='3'");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    data = "";
    for (i=0;i<obj.mLogs.size();i++) {
        data += "logID : "+QString::number(obj.mLogs.at(i).logID)+", ";
        data += "userID : "+QString::number(obj.mLogs.at(i).userID)+", ";
        data += "timeStamp : "+obj.mLogs.at(i).timeStamp.toString("yyyy-MM-dd HH-mm-ss")+", ";
        data += "timeStamp (UTC): "+obj.mLogs.at(i).timeStamp.toUTC().toString("yyyy-MM-dd HH:mm:ss")+", ";
        data += "description : "+obj.mLogs.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    //<percobaan

    return a.exec();
}
