#include <QtAndroid>
#include <QtAndroidExtras>
#include <QRemoteObjectHost>
#include <QSignalMapper>
#include <QSettings>
#include "remote.h"
#include "runtime/server.h"
#include "rep_remote_replica.h"


void checkSettingsValue(QSettings *settings){
    if((!settings->contains("isLoggedIn"))){
        settings->setValue("isLoggedIn",false);
    }
    if((!settings->contains("isOnline"))){
        settings->setValue("isOnline",false);
    }
}

int main(int argc, char *argv[])
{
    QAndroidService::setApplicationName("Witchcraft House");
    QAndroidService::setOrganizationDomain("house.witchcraft.web.id");
    QAndroidService::setOrganizationName("Witchcraft");
    QAndroidService a(argc,argv);

    QSettings settings;
    checkSettingsValue(&settings);

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

//    QTimer *timer = new QTimer;
//    timer->setInterval(5000);
//    timer->setSingleShot(false);
//    QSignalMapper *signalMapper = new QSignalMapper;
//    QObject::connect(timer,SIGNAL(timeout()),signalMapper,SLOT(map()));
//    signalMapper->setMapping(timer,"Azure");
//    QObject::connect(signalMapper,SIGNAL(mapped(QString)),rep.data(),SLOT(ping(QString)));
//    timer->start();
    Server *server = new Server;
    server->setRemote(rep.data());

    return a.exec();
}
