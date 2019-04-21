#include <QCoreApplication>
#include <QSqlDatabase>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QTextStream>
#include <QSettings>
#include <QUuid>
#include <QThread>

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
#include "Boundary/simplesmtp.h"
#include "Boundary/cronscheduler.h"

//Controller
#include "Control/usercontroller.h"
#include "Control/devicecontroller.h"
#include "Control/schedulecontroller.h"
#include "Control/sharedcontroller.h"

bool insertIconData(QSqlDatabase *db){
    /*mItems.append({ 0, QStringLiteral("default") });
    mItems.append({ 1, QStringLiteral("house") });
    mItems.append({ 2, QStringLiteral("lamp") });
    mItems.append({ 3, QStringLiteral("switch") });
    mItems.append({ 4, QStringLiteral("outlet") });
    mItems.append({ 5, QStringLiteral("fan") });
    mItems.append({ 6, QStringLiteral("thermometer") });
    mItems.append({ 7, QStringLiteral("lock") });
    mItems.append({ 8, QStringLiteral("key") });
    mItems.append({ 9, QStringLiteral("fire") });
    mItems.append({ 10, QStringLiteral("AC") });
    mItems.append({ 11, QStringLiteral("cctv") });
    mItems.append({ 12, QStringLiteral("bell") });
    mItems.append({ 13, QStringLiteral("sun") });
    mItems.append({ 14, QStringLiteral("moon") });
    mItems.append({ 15, QStringLiteral("thermostat") });
    mItems.append({ 16, QStringLiteral("power") });
    mItems.append({ 17, QStringLiteral("door") });
    mItems.append({ 18, QStringLiteral("water") });
    mItems.append({ 19, QStringLiteral("leaf") });*/

    QString textQuery = "INSERT INTO `Icon`(`iconID`, `iconName`) VALUES \
                        ('0','default'),\
                        ('1','house'),\
                        ('2','lamp'),\
                        ('3','switch'),\
                        ('4','outlet'),\
                        ('5','fan'),\
                        ('6','thermometer'),\
                        ('7','lock'),\
                        ('8','key'),\
                        ('9','fire'),\
                        ('10','AC'),\
                        ('11','cctv'),\
                        ('12','bell'),\
                        ('13','sun'),\
                        ('14','moon'),\
                        ('15','thermostat'),\
                        ('16','power'),\
                        ('17','door'),\
                        ('18','water'),\
                        ('19','leaf')\
                        ;";
    QSqlQuery query;
    bool ok = false;

    if(db->open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            QTextStream(stdout) << "no error when creating icon\n";
        }
        else {
            QTextStream(stdout) << "Error Query Icon : " << query.lastError().text() << "\n";
        }
    }
    return ok;
}

bool insertPinTypeData(QSqlDatabase *db){
    /*mItems.append({ 0, QStringLiteral("default") });
    mItems.append({ 1, QStringLiteral("switch") });
    mItems.append({ 2, QStringLiteral("textout") });
    mItems.append({ 3, QStringLiteral("tempc") });
    mItems.append({ 4, QStringLiteral("textfield") });
    mItems.append({ 5, QStringLiteral("textarea") });
    mItems.append({ 6, QStringLiteral("tumbler") });
    mItems.append({ 7, QStringLiteral("spinbox") });
    mItems.append({ 8, QStringLiteral("combobox") });
    mItems.append({ 9, QStringLiteral("webview") });
    mItems.append({ 10,QStringLiteral("rangeslider")});
    mItems.append({ 11,QStringLiteral("colordialog")});
    mItems.append({ 12,QStringLiteral("slider")});*/

    QString textQuery = "INSERT INTO `PinType`(`pinTypeID`, `pinTypeName`) VALUES \
                        ('0','default'),\
                        ('1','switch'),\
                        ('2','textout'),\
                        ('3','tempc'),\
                        ('4','textfield'),\
                        ('5','textarea'),\
                        ('6','tumbler'),\
                        ('7','spinbox'),\
                        ('8','combobox'),\
                        ('9','webview'),\
                        ('10','rangeslider'),\
                        ('11','colordialog'),\
                        ('12','slider')\
                        ;";
    QSqlQuery query;
    bool ok = false;

    if(db->open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            QTextStream(stdout) << "no error when creating pinType\n";
        }
        else {
            QTextStream(stdout) << "Error Query pinType : " << query.lastError().text() << "\n";
        }
    }
    return ok;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Witchcraft House Server");
    QCoreApplication::setOrganizationDomain("house.witchcraft.web.id");
    QCoreApplication::setOrganizationName("Witchcraft");

    QString secret;
    QSettings settings;

    //[SECRET]
    if(settings.contains("secret")){
        secret = settings.value("secret").toString();
    }
    else {
        secret = "OGt8oV8b0RvaQnz";
        settings.setValue("secret",secret);
    }
    //[SECRET]

    //[INIT DATABASE]
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //hostname
    if (settings.contains("database/hostname")) {
        db.setHostName(settings.value("database/hostname").toString());
    }
    else{
        settings.setValue("database/hostname","localhost");
        db.setHostName("localhost");
    }
    //databasename
    if (settings.contains("database/databasename")) {
        db.setDatabaseName(settings.value("database/databasename").toString());
    }
    else{
        settings.setValue("database/databasename","witchcrafthouse");
        db.setDatabaseName("witchcrafthouse");
    }
    //username
    if (settings.contains("database/username")) {
        db.setUserName(settings.value("database/username").toString());
    }
    else{
        settings.setValue("database/username","admin");
        db.setUserName("admin");
    }
    //password
    if (settings.contains("database/password")) {
        db.setPassword(settings.value("database/password").toString());
    }
    else{
        settings.setValue("database/password","azsx312");
        db.setPassword("azsx312");
    }
    //port
    if (settings.contains("database/port")) {
        db.setPort(settings.value("database/port").toInt());
    }
    else{
        settings.setValue("database/port",3306);
        db.setPort(3306);
    }
    bool ok = db.open();
    if (!ok){
        QTextStream(stdout) << "ERROR: "+ db.lastError().text() + "\n";
    }
    //[INIT DATABASE]

    //[INIT ICON AND PIN TYPE IF NEEDED]
    if (settings.contains("init")) {
        if(settings.value("init").toBool()){
            insertIconData(&db);
            insertPinTypeData(&db);
            settings.setValue("init",false);
        }
    }
    else{
        insertIconData(&db);
        insertPinTypeData(&db);
        settings.setValue("init",false);
    }
    //[INIT ICON AND PIN TYPE IF NEEDED]

    //[WEBSOCKET SERVER AND SCHEDULER]
    quint16 serverport;
    //serverport
    if (settings.contains("serverport")) {
        serverport = QString::number(settings.value("serverport").toInt()).toUShort();
    }
    else{
        settings.setValue("serverport",9000);
        serverport = 9000;
    }
    WebsocketServer *server = new WebsocketServer(serverport);
    server->setSecret(secret);
    server->setDatabase(&db);
    //[WEBSOCKET SERVER AND SCHEDULER]

    //[CONTROLER AND STUFF]
    UserController *UC = new UserController(&db);
    UC->setSecret(secret);
    DeviceController *DC = new DeviceController(&db);
    DC->setSecret(secret);
    ScheduleController *SC = new ScheduleController(&db);
    SharedController *ShC = new SharedController(&db);

    server->setUC(UC);
    server->setDC(DC);
    server->setSC(SC);
    server->setShC(ShC);

//    QThread *threadUC = new QThread;
//    QThread *threadDC = new QThread;
//    QThread *threadSC = new QThread;
//    QThread *threadShC = new QThread;

//    UC->moveToThread(threadUC);
//    DC->moveToThread(threadDC);
//    SC->moveToThread(threadSC);
//    ShC->moveToThread(threadShC);

//    threadUC->start();
//    threadDC->start();
//    threadSC->start();
//    threadShC->start();
    //[CONTROLER AND STUFF]

    //[SCHEDULER AND SMTP]
    CronScheduler *scheduler = new CronScheduler;
    server->setCronScheduler(scheduler);
    QObject::connect(SC,SIGNAL(createNewCron(QUuid, QString, QUuid, QString, int)),scheduler,SLOT(createNewCron(QUuid, QString, QUuid, QString, int)));
    QObject::connect(SC,SIGNAL(editCron(QUuid, QString, QUuid, QString, int)),scheduler,SLOT(editCron(QUuid, QString, QUuid, QString, int)));
    QObject::connect(SC,SIGNAL(deleteCron(QUuid)),scheduler,SLOT(deleteCron(QUuid)));
    QObject::connect(scheduler,SIGNAL(setPinValue(QJsonObject,int)),DC,SLOT(setPinValue(QJsonObject,int)));
    SC->initAllCron();
    SimpleSMTP *smtp = new SimpleSMTP("witchcraftsystem@gmail.com","W1tchCr4ftH0us3","smtp.gmail.com");
    QObject::connect(server,SIGNAL(sendMail(QString,QString,QString)),smtp,SLOT(sendMail(QString,QString,QString)));
    //[SCHEDULER AND SMTP]

    //[QOBJECT CONNECTION]
    QObject::connect(server, &WebsocketServer::closed, &a, &QCoreApplication::quit);
    QObject::connect(UC,SIGNAL(sendMail(QString,QString,QString)),smtp,SLOT(sendMail(QString,QString,QString)));
    //QObject::connect(UC,SIGNAL(sendMail(QString,QString,QString)),server,SIGNAL(sendMail(QString,QString,QString)));
    QObject::connect(DC,SIGNAL(sendMail(QString,QString,QString)),server,SIGNAL(sendMail(QString,QString,QString)));
    QObject::connect(DC,SIGNAL(broadcastToDevice(QUuid,QJsonObject)),server,SLOT(broadcastToDevice(QUuid,QJsonObject)));
    QObject::connect(DC,SIGNAL(deletedDevice(QUuid)),server,SLOT(deletedDevice(QUuid)));
    QObject::connect(DC,SIGNAL(deletedPin(QUuid,int)),SC,SLOT(deletedPin(QUuid,int)));
    //QObject::connect(DC,SIGNAL(deletedPin(QUuid,int)),ShC,SLOT(deletedPin(QUuid,int)));
    QObject::connect(DC,SIGNAL(deletedGroup(int,int)),ShC,SLOT(deletedGroup(int,int)));
    QObject::connect(DC,SIGNAL(broadcastToAllUserControlDevice(int,QJsonObject)),server,SLOT(broadcastToAllUserControlDevice(int,QJsonObject)));
    //QObject::connect(DC,SIGNAL(broadcastToDevice(QUuid,QJsonObject)),server,SLOT(broadcastToDevice(QUuid,QJsonObject)));
    //[QOBJECT CONNECTION]

    return a.exec();
}
