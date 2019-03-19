#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#include <QAndroidJniObject>

#include "rep_pingpong_replica.h"
#include "coba.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QAndroidJniObject::callStaticMethod<void>("com/kdab/training/MyService",
                                              "startMyService",
                                              "(Landroid/content/Context;)V",
                                              QtAndroid::androidActivity().object());

    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
    QSharedPointer<PingPongReplica> rep(repNode.acquire<PingPongReplica>());
    engine.rootContext()->setContextProperty("pingPong", rep.data());
    bool res = rep->waitForSource();
    Q_ASSERT(res);
    //rep->ping("Hello");

//    int number = 100;
//    jint randomValue = number;
//    QAndroidJniObject title = QAndroidJniObject::fromString("From client");
//    QAndroidJniObject body = QAndroidJniObject::fromString("Holla");
//    jint keluaran = QAndroidJniObject::callStaticMethod<jint>("com/kdab/training/ServiceQt",
//                                           "notify",
//                                           "(ILjava/lang/String;Ljava/lang/String;)I",
//                                           randomValue,
//                                           title.object<jstring>(),
//                                           body.object<jstring>());
//    qDebug() << keluaran;
    Coba *coba = new Coba;
    coba->setPath();
    QObject::connect(rep.data(),SIGNAL(pong(QString)),coba,SLOT(notification(QString)));

    return app.exec();
}
