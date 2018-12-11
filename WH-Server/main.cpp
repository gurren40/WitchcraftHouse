#include <QCoreApplication>
#include <QSqlDatabase>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "websocketserver.h"
#include "Controller/devicecontroller.h"

static QJsonObject loadSetting(){
    QFile loadFile(QStringLiteral("/home/aditiya/QtProjects/witchcrafthouse/SettingFolder/setting.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    QJsonObject json = loadDoc.object();
    return json;
}

static QSqlDatabase setDatabase() {
    QJsonObject setting = loadSetting();
    QSqlDatabase db = QSqlDatabase::addDatabase(setting["dbtype"].toString());
    db.setHostName(setting["hostname"].toString());
    db.setDatabaseName(setting["dbname"].toString());
    db.setUserName(setting["dbusername"].toString());
    db.setPassword(setting["dbpassword"].toString());
    bool ok = db.open();
    if (ok){
        return db;
    } else {
        //qDebug() << "ERROR: "+ db.lastError().text();
        return db;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase db = setDatabase();
    WebsocketServer server(1234);
    DeviceController c_device(&db);

    QObject::connect(&server,&WebsocketServer::toDeviceController,&c_device,&DeviceController::fromWebsocket);
    QObject::connect(&c_device,&DeviceController::sendMessegeToControllDevice,&server,&WebsocketServer::sendMessageToControllDevice);

    return a.exec();
}
