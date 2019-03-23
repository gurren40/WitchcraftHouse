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

int main(int argc, char *argv[])
{
    QGuiApplication::setApplicationName("Witchcraft House");
    QAndroidService::setOrganizationDomain("house.witchcraft.web.id");
    QGuiApplication::setOrganizationName("Witchcraft");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QAndroidJniObject::callStaticMethod<void>("id/web/witchcraft/house/MyService",
                                                  "startMyService",
                                                  "(Landroid/content/Context;)V",
                                                  QtAndroid::androidActivity().object());
    QQmlApplicationEngine engine;
    engine.load(QUrl("qrc:/qml/main.qml"));
    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
    QSharedPointer<RemoteReplica> rep(repNode.acquire<RemoteReplica>());
    engine.rootContext()->setContextProperty("pingPong", rep.data());
    bool res = rep->waitForSource();
    Q_ASSERT(res);

    QTimer *timer = new QTimer;
    timer->setInterval(5000);
    timer->setSingleShot(false);
    QSignalMapper *signalMapper = new QSignalMapper;
    QObject::connect(timer,SIGNAL(timeout()),signalMapper,SLOT(map()));
    signalMapper->setMapping(timer,"Azerbajian");
    QObject::connect(signalMapper,SIGNAL(mapped(QString)),rep.data(),SLOT(ping(QString)));
    timer->start();

    return app.exec();
}

