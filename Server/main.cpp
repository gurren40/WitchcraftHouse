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
#include "Boundary/simplesmtp.h"
#include "Boundary/cronscheduler.h"


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
    QString secret = "OGt8oV8b0RvaQnz";
    //percobaanEntity();
    //percobaanController();
    //percobaanEmail();

    QSqlDatabase db = setDatabase();
    WebsocketServer *server = new WebsocketServer(9000);
    CronScheduler *scheduler = new CronScheduler;
    server->setDatabase(&db);
    server->setCronScheduler(scheduler);

    //init all scheduler
    ScheduleController SC(&db);
    QObject::connect(&SC,SIGNAL(createNewCron(QUuid, QString, QUuid, QString, int)),scheduler,SLOT(createNewCron(QUuid, QString, QUuid, QString, int)));
    SC.initAllCron();
    SC.~ScheduleController();

    //smtp
    SimpleSMTP *smtp = new SimpleSMTP("witchcraftsystem@gmail.com","W1tchCr4ftH0us3","smtp.gmail.com");
    QObject::connect(server,SIGNAL(sendMail(QString,QString,QString)),smtp,SLOT(sendMail(QString,QString,QString)));
    //QObject::connect();
    QObject::connect(server, &WebsocketServer::closed, &a, &QCoreApplication::quit);

    return a.exec();
}
