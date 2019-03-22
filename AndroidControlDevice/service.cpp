#include <QtAndroid>
#include <QtAndroidExtras>
#include <QRemoteObjectHost>
#include <QSignalMapper>
#include "remote.h"
#include "rep_remote_replica.h"
#include "services/notification.h"

int main(int argc, char *argv[])
{
    QAndroidService a(argc,argv);

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
    Remote remoteServer;
    //srcNode.enableRemoting(&remoteServer);
    if(srcNode.enableRemoting(&remoteServer)){
        qDebug() << "qwerty enabled remoting";
    }
    else {
        qDebug() << "not enabled qwerty";
    }

    QRemoteObjectNode repNode;
    repNode.connectToNode(QUrl(QStringLiteral("local:replica")));
    QSharedPointer<RemoteReplica> rep(repNode.acquire<RemoteReplica>());
    bool res = rep->waitForSource();
    Q_ASSERT(res);

    Notification *notify = new Notification;
    notify->setJavaClass("id/web/witchcraft/house/MyService");
    QObject::connect(rep.data(),SIGNAL(pong(QString)),notify,SLOT(notify(QString)));

    QTimer *timer = new QTimer;
    timer->setInterval(5000);
    timer->setSingleShot(false);
    QSignalMapper *signalMapper = new QSignalMapper;
    QObject::connect(timer,SIGNAL(timeout()),signalMapper,SLOT(map()));
    signalMapper->setMapping(timer,"Azure");
    QObject::connect(signalMapper,SIGNAL(mapped(QString)),rep.data(),SLOT(ping(QString)));
    timer->start();

    return a.exec();
}
