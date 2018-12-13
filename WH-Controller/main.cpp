#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QQmlContext>

#include "websocketconnection.h"
#include "devicelist.h"
#include "devicemodel.h"
#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QUrl url("ws://localhost:1234/controll/?username=aditiyasidabutar@student.undip.ac.id&password=qwerty1234");

    //qdebug thing
    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(app);
    bool debug = parser.isSet(dbgOption);
    //end of qdebug thing

    //bagian delegate

    qmlRegisterType<DeviceModel>("Device", 1, 0, "DeviceModel");
    qmlRegisterUncreatableType<DeviceList>("Device",1,0,"DeviceList",
                                         QStringLiteral("DeviceList should not created in QML"));

    DeviceList deviceList;
    backend backhand;
    WebsocketConnection client(url, debug);

    QObject::connect(&backhand,&backend::getDeviceValueDammnit,&deviceList,&DeviceList::initRequestAllDevice); //ok
    QObject::connect(&backhand,&backend::setValueDevice,&deviceList,&DeviceList::requestSetDeviceValue); //ok
    QObject::connect(&deviceList,&DeviceList::sendMessageToServer,&client,&WebsocketConnection::sendMessage); //ok
    QObject::connect(&client,&WebsocketConnection::getDeviceList,&deviceList,&DeviceList::rewriteAllItem); //ok
    QObject::connect(&client,&WebsocketConnection::setDeviceValue,&deviceList,&DeviceList::setDeviceValue);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("deviceList", &deviceList);
    engine.rootContext()->setContextProperty("backend", &backhand);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
