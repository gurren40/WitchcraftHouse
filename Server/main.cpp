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

    Shared obj(&db);
    //user.setDatabase(&db);
    json = obj.create(8,6,1,4,2,"Kakakakakakak","Wkwkwkwkwk");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    for (i=0;i<obj.mShareds.size();i++) {
        data += "sharedID : "+QString::number(obj.mShareds.at(i).sharedID)+", ";
        data += "sharedBy : "+QString::number(obj.mShareds.at(i).sharedBy)+", ";
        data += "sharedByName : "+obj.mShareds.at(i).sharedByName+", ";
        data += "sharedTo : "+QString::number(obj.mShareds.at(i).sharedTo)+", ";
        data += "sharedToName : "+obj.mShareds.at(i).sharedToName+", ";
        data += "groupID : "+QString::number(obj.mShareds.at(i).groupID)+", ";
        data += "groupName : "+obj.mShareds.at(i).groupName+", ";
        data += "pinID : "+QString::number(obj.mShareds.at(i).pinID)+", ";
        data += "pinUUID : "+obj.mShareds.at(i).pinUUID.toString(QUuid::WithoutBraces)+", ";
        data += "pinName : "+obj.mShareds.at(i).pinName+", ";
        data += "sharedName : "+obj.mShareds.at(i).sharedName+", ";
        data += "description : "+obj.mShareds.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    json = obj.update(2,21,6,1,4,2,"LALALALALA","harharhar");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.deletes("sharedID='3'");
    QTextStream(stdout) << json["error"].toString() << "\n";

    json = obj.read();
    QTextStream(stdout) << json["error"].toString() << "\n";

    data = "";
    for (i=0;i<obj.mShareds.size();i++) {
        data += "sharedID : "+QString::number(obj.mShareds.at(i).sharedID)+", ";
        data += "sharedBy : "+QString::number(obj.mShareds.at(i).sharedBy)+", ";
        data += "sharedByName : "+obj.mShareds.at(i).sharedByName+", ";
        data += "sharedTo : "+QString::number(obj.mShareds.at(i).sharedTo)+", ";
        data += "sharedToName : "+obj.mShareds.at(i).sharedToName+", ";
        data += "groupID : "+QString::number(obj.mShareds.at(i).groupID)+", ";
        data += "groupName : "+obj.mShareds.at(i).groupName+", ";
        data += "pinID : "+QString::number(obj.mShareds.at(i).pinID)+", ";
        data += "pinUUID : "+obj.mShareds.at(i).pinUUID.toString(QUuid::WithoutBraces)+", ";
        data += "pinName : "+obj.mShareds.at(i).pinName+", ";
        data += "sharedName : "+obj.mShareds.at(i).sharedName+", ";
        data += "description : "+obj.mShareds.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    //<percobaan

    return a.exec();
}
