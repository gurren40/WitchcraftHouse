#include <QAndroidService>
#include <QAndroidJniObject>
#include <QDebug>
#include <QTimer>
#include <QCoreApplication>
#include "rep_pingpong_source.h"
#include "rep_pingpong_replica.h"
#include <QThread>
#include <QSignalMapper>

#include "coba.h"

class PingPong : public PingPongSource {
public slots:
    // PingPongSource interface
    void ping(const QString &msg) override {
        qDebug() << msg;
        qDebug() << "selamatkah sampai disini?";
        emit pong(msg + " from server");
    }
};

int main(int argc, char *argv[])
{
    QAndroidService app(argc, argv);
    qDebug() << "service started";

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
    PingPong pingPongServer;
    srcNode.enableRemoting(&pingPongServer);

    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
    QSharedPointer<PingPongReplica> rep(repNode.acquire<PingPongReplica>());
    //engine.rootContext()->setContextProperty("pingPong", rep.data());
    bool res = rep->waitForSource();
    Q_ASSERT(res);
    rep->ping("Hollala");


    Coba *coba = new Coba;
    coba->setPath("com/kdab/training/MyService");
    //coba->notification();

    QSignalMapper *signalMapper = new QSignalMapper;
    QTimer *timer = new QTimer;

    QObject::connect(timer,SIGNAL(timeout()),signalMapper,SLOT(map()));
    QObject::connect(timer,SIGNAL(timeout()),coba,SLOT(notification()));
    signalMapper->setMapping(timer, "hahahahaha");
    QObject::connect(signalMapper,SIGNAL(mapped(QString)),rep.data(),SLOT(ping(QString)));
    //QTimer::singleShot(10000,rep.data(),SLOT(ping()));
    timer->setSingleShot(false);
    timer->start(10000);

    return app.exec();
}
