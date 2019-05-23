#include <QQuickStyle>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectNode>
#include <QTimer>
#include <QSignalMapper>
#include <QIcon>
#include <QMetaType>
#include <QtSvg>
#include <QObject>

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

//non editable
#include "models/iconmodel.h"
#include "models/pintypemodel.h"
#include "lists/iconlist.h"
#include "lists/pintypelist.h"

//logs
#include "lists/loglist.h"
#include "models/logviewmodel.h"
#include "models/pinlogviewmodel.h"
#include "lists/loglistview.h"
#include "lists/pinloglistview.h"

//platform specificfunctions
#include "linuxFunctions/externalfunctions.h"

int main(int argc, char *argv[])
{
    //inisialisasi GUI & Environment
    QApplication::setApplicationName("Witchcraft House");
    QApplication::setOrganizationDomain("house.witchcraft.web.id");
    QApplication::setOrganizationName("Witchcraft");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QIcon::setThemeName("witchcraft");

    qRegisterMetaType<QJsonObject>();

    //panggil service
    ExternalFunctions *externalFunction = new ExternalFunctions;
    externalFunction->callAndroidService();

    //Register model & list
    qmlRegisterType<PinModel>("Pin", 1, 0, "PinModel");
    qmlRegisterType<DeviceModel>("Device", 1, 0, "DeviceModel");
    qmlRegisterType<GroupModel>("Group", 1, 0, "GroupModel");
    qmlRegisterType<ScheduleModel>("Schedule", 1, 0, "ScheduleModel");
    qmlRegisterType<SharedModel>("Shared", 1, 0, "SharedModel");
    qmlRegisterType<ControlDeviceModel>("ControlDevice", 1, 0, "ControlDeviceModel");
    //non editable
    qmlRegisterType<IconModel>("Icon",1,0,"IconModel");
    qmlRegisterType<PinTypeModel>("PinType",1,0,"PinTypeModel");
    qmlRegisterType<LogViewModel>("LogView",1,0,"LogViewModel");
    qmlRegisterType<PinLogViewModel>("LogView",1,0,"PinLogViewModel");

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
    //nn
    qmlRegisterUncreatableType<IconList>("Icon", 1, 0, "IconList",
        QStringLiteral("IconList should not be created in QML"));
    qmlRegisterUncreatableType<PinTypeList>("PinType", 1, 0, "PinTypeList",
        QStringLiteral("PinTypeList should not be created in QML"));
    //logs
    qmlRegisterUncreatableType<LogList>("LogView", 1, 0, "LogList",
        QStringLiteral("LogView should not be created in QML"));
    qmlRegisterUncreatableType<LogListView>("LogView", 1, 0, "LogListView",
        QStringLiteral("LogListView should not be created in QML"));
    qmlRegisterUncreatableType<PinLogListView>("LogView", 1, 0, "PinLogListView",
        QStringLiteral("PinLogListView should not be created in QML"));


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
    //inisialisasi non editable
    IconList iconList;
    PinTypeList pinTypeList;
    //logs
    LogListView logListView;
    PinLogListView pinLogListView;
    LogList logList;
    logList.setRemote(rep.data());
    logList.setLoglistview(&logListView);
    logList.setPinloglistview(&pinLogListView);

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
    clientApp.setLogList(&logList);

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
    engine.rootContext()->setContextProperty(QStringLiteral("iconList"), &iconList);
    engine.rootContext()->setContextProperty(QStringLiteral("pinTypeList"), &pinTypeList);

    //logs
    engine.rootContext()->setContextProperty(QStringLiteral("logListView"), &logListView);
    engine.rootContext()->setContextProperty(QStringLiteral("pinLogListView"), &pinLogListView);
    engine.rootContext()->setContextProperty(QStringLiteral("logList"), &logList);

    engine.load(QUrl("qrc:/qml/main.qml"));

    //[OBJECT CONNECTION]
    QObject::connect(&user,&User::restartServiceSig,externalFunction,&ExternalFunctions::callAndroidService);
    //[OBJECT CONNECTION]

    //set device model
    user.setThisDeviceModel(externalFunction->getDeviceModel());

    return app.exec();
}

