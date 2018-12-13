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

    return loadDoc.object();;
}

static QSqlDatabase setDatabase() {
    QJsonObject setting = loadSetting();
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QTextStream(stdout) << setting["dbhostname"].toString() << "\n";
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
    QSqlDatabase db = setDatabase();
    WebsocketServer server(1234);
    DeviceController c_device(&db);

    QObject::connect(&server,&WebsocketServer::toDeviceController,&c_device,&DeviceController::fromWebsocket);
    QObject::connect(&c_device,&DeviceController::sendMessegeToControllDevice,&server,&WebsocketServer::sendMessageToControllDevice);
    QObject::connect(&c_device,&DeviceController::sendMessegeToDevice,&server,&WebsocketServer::sendMessageToDevice);

    return a.exec();
}
