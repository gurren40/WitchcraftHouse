#include <QGuiApplication>
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectNode>
#include <QTimer>
#include <QSignalMapper>

#include "rep_remote_replica.h"
#include "models/pinmodel.h"
#include "models/devicemodel.h"
#include "models/groupmodel.h"
#include "models/schedulemodel.h"
#include "models/sharedmodel.h"
#include "lists/pinlist.h"
#include "lists/devicelist.h"
#include "lists/grouplist.h"
#include "lists/schedulelist.h"
#include "lists/sharedlist.h"

int main(int argc, char *argv[])
{
    //inisialisasi GUI & Environment
    QGuiApplication::setApplicationName("Witchcraft House");
    QAndroidService::setOrganizationDomain("house.witchcraft.web.id");
    QGuiApplication::setOrganizationName("Witchcraft");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //panggil service
    QAndroidJniObject::callStaticMethod<void>("id/web/witchcraft/house/MyService",
                                                  "startMyService",
                                                  "(Landroid/content/Context;)V",
                                                  QtAndroid::androidActivity().object());

    //Register model & list
    qmlRegisterType<PinModel>("Pin", 1, 0, "PinModel");
    qmlRegisterType<DeviceModel>("Device", 1, 0, "DeviceModel");
    qmlRegisterType<GroupModel>("Group", 1, 0, "GroupModel");
    qmlRegisterType<ScheduleModel>("Schedule", 1, 0, "ScheduleModel");
    qmlRegisterType<SharedModel>("Shared", 1, 0, "SharedModel");

    qmlRegisterUncreatableType<PinList>("Pin", 1, 0, "PinList",
        QStringLiteral("PinList should not be created in QML"));
    qmlRegisterUncreatableType<DeviceList>("Device", 1, 0, "DeviceList",
        QStringLiteral("DeviceList should not be created in QML"));
    qmlRegisterUncreatableType<GroupList>("Group", 1, 0, "GroupList",
        QStringLiteral("GroupList should not be created in QML"));
    qmlRegisterUncreatableType<ScheduleList>("Schedule", 1, 0, "ScheduleList",
        QStringLiteral("ScheduleList should not be created in QML"));
    qmlRegisterUncreatableType<SharedList>("Shared", 1, 0, "SharedList",
        QStringLiteral("SharedList should not be created in QML"));

    //inisialisasi list
    PinList pinList;
    DeviceList deviceList;
    GroupList groupList;
    ScheduleList scheduleList;
    SharedList sharedList;
    PinList sharedPinList;

    QQmlApplicationEngine engine;

    //inisialisasi list di qml engine
    engine.rootContext()->setContextProperty(QStringLiteral("pinList"), &pinList);
    engine.rootContext()->setContextProperty(QStringLiteral("deviceList"), &deviceList);
    engine.rootContext()->setContextProperty(QStringLiteral("groupList"), &groupList);
    engine.rootContext()->setContextProperty(QStringLiteral("scheduleList"), &scheduleList);
    engine.rootContext()->setContextProperty(QStringLiteral("sharedList"), &sharedList);
    engine.rootContext()->setContextProperty(QStringLiteral("sharedPinList"), &sharedPinList);

    engine.load(QUrl("qrc:/qml/main.qml"));

    //panggil remote object
    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
    QSharedPointer<RemoteReplica> rep(repNode.acquire<RemoteReplica>());
    engine.rootContext()->setContextProperty("pingPong", rep.data());
    bool res = rep->waitForSource();
    Q_ASSERT(res);

//    QTimer *timer = new QTimer;
//    timer->setInterval(5000);
//    timer->setSingleShot(false);
//    QSignalMapper *signalMapper = new QSignalMapper;
//    QObject::connect(timer,SIGNAL(timeout()),signalMapper,SLOT(map()));
//    signalMapper->setMapping(timer,"Azerbajian");
//    QObject::connect(signalMapper,SIGNAL(mapped(QString)),rep.data(),SLOT(ping(QString)));
//    timer->start();
    return app.exec();
}

