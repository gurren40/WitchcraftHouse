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

static void percobaanEntity(){
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
        data += "timeStamp : "+obj.mLogs.at(i).timeStamp.toString("yyyy-MM-dd HH:mm:ss")+", ";
        data += "timeStamp (UTC): "+obj.mLogs.at(i).timeStamp.toUTC().toString("yyyy-MM-dd HH:mm:ss")+", ";
        data += "description : "+obj.mLogs.at(i).description+"\n";
    }
    QTextStream(stdout) << data << "\n";

    QTextStream(stdout) << QUrl(QUrl("http://localhost:8000/device?token=asdfasdfasdfewrawer45wrg").toString(QUrl::RemoveUserInfo)).query() << "\n";

    //<percobaan
}

static void percobaanController(){
    QJsonObject jsonIn;
    QJsonObject user;
    QJsonArray jsonArrayIn;
    QJsonObject jsonOut;
    QSqlDatabase db = setDatabase();
    QString secret = "OGt8oV8b0RvaQnz";
    UserController uc(&db);

    user["email"] = "aditiyasidabutar@gmail.com";
    user["password"] = "somepass";
    user["name"] = "aditiya";
    jsonArrayIn.append(user);
/*
    user["email"] = "sidabutaraditiya@gmail.com";
    user["password"] = "somepass";
    user["name"] = "dwi putra";
    jsonArrayIn.append(user);

    user["email"] = "sidabutarsidabutar@gmail.com";
    user["password"] = "somepass";
    user["name"] = "sidabutar";
    jsonArrayIn.append(user);
*/
    jsonIn["requestLoginToken"] = jsonArrayIn;

    jsonOut = uc.requestLoginToken(jsonIn);
    QJsonDocument document(jsonOut);
    QTextStream(stdout) << document.toJson() << "\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString secret = "OGt8oV8b0RvaQnz";
    percobaanController();
    return a.exec();
}
