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
#include "lists/pinlist.h"

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
    qmlRegisterUncreatableType<PinList>("Pin", 1, 0, "PinList",
        QStringLiteral("PinList should not be created in QML"));

    //inisialisasi list
    PinList pinList;

    QQmlApplicationEngine engine;

    //inisialisasi list di qml engine
    engine.rootContext()->setContextProperty(QStringLiteral("pinList"), &pinList);

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

