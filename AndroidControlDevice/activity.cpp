#include <QGuiApplication>
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectNode>
#include <QTimer>
#include <QSignalMapper>
#include <QIcon>

#include "rep_remote_replica.h"
#include "models/pinmodel.h"
#include "models/devicemodel.h"
#include "models/groupmodel.h"
#include "models/schedulemodel.h"
#include "models/sharedmodel.h"
#include "models/controldevicemodel.h"
#include "lists/pinlist.h"
#include "lists/devicelist.h"
#include "lists/grouplist.h"
#include "lists/schedulelist.h"
#include "lists/sharedlist.h"
#include "lists/controldevicelist.h"

#include "objects/user.h"
#include "runtime/client.h"

int main(int argc, char *argv[])
{
    //inisialisasi GUI & Environment
    QGuiApplication::setApplicationName("Witchcraft House");
    QAndroidService::setOrganizationDomain("house.witchcraft.web.id");
    QGuiApplication::setOrganizationName("Witchcraft");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QIcon::setThemeName("witchcraft");

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
    qmlRegisterType<ControlDeviceModel>("ControlDevice", 1, 0, "ControlDeviceModel");

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
    qmlRegisterUncreatableType<ControlDeviceList>("ControlDevice", 1, 0, "ControlDeviceList",
        QStringLiteral("ControlDeviceList should not be created in QML"));

    //panggil remote object
    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
    QSharedPointer<RemoteReplica> rep(repNode.acquire<RemoteReplica>());
    bool res = rep->waitForSource();
    Q_ASSERT(res);

    //inisialisasi list
    PinList pinList;
    pinList.setRemote(rep.data());
    DeviceList deviceList;
    deviceList.setRemote(rep.data());
    GroupList groupList;
    groupList.setRemote(rep.data());
    ScheduleList scheduleList;
    scheduleList.setRemote(rep.data());
    SharedList sharedList;
    sharedList.setRemote(rep.data());
    PinList sharedPinList;
    sharedPinList.setRemote(rep.data());
    ControlDeviceList controlDeviceList;
    controlDeviceList.setRemote(rep.data());
    User user; //inisialisasi objek user
    user.setRemote(rep.data());

    //inisialisasi client
    Client clientApp;
    clientApp.setRemote(rep.data());
    clientApp.setPinList(&pinList);
    clientApp.setDeviceList(&deviceList);
    clientApp.setGroupList(&groupList);
    clientApp.setScheduleList(&scheduleList);
    clientApp.setSharedList(&sharedList);
    clientApp.setSharedPinList(&sharedPinList);
    clientApp.setControlDeviceList(&controlDeviceList);
    clientApp.setUser(&user);

    //inisialisasi list di qml engine
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("pinList"), &pinList);
    engine.rootContext()->setContextProperty(QStringLiteral("deviceList"), &deviceList);
    engine.rootContext()->setContextProperty(QStringLiteral("groupList"), &groupList);
    engine.rootContext()->setContextProperty(QStringLiteral("scheduleList"), &scheduleList);
    engine.rootContext()->setContextProperty(QStringLiteral("sharedList"), &sharedList);
    engine.rootContext()->setContextProperty(QStringLiteral("sharedPinList"), &sharedPinList);
    engine.rootContext()->setContextProperty(QStringLiteral("controlDeviceList"), &controlDeviceList);
    engine.rootContext()->setContextProperty(QStringLiteral("user"), &user);

    engine.load(QUrl("qrc:/qml/main.qml"));

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

