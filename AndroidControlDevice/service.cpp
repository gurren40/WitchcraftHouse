#include <QtAndroid>
#include <QtAndroidExtras>
#include <QRemoteObjectHost>
#include <QSignalMapper>
#include <QSettings>
#include "androidFunctions/externalfunctions.h"
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

    qRegisterMetaType<QJsonObject>();

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
    Remote remoteServer;
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
    ExternalFunctions *extrnalFunctions = new ExternalFunctions;

    QObject::connect(notify,&Notification::sendNotificationSig,extrnalFunctions,&ExternalFunctions::sendNotification);

    Server *server = new Server;
    server->setRemote(rep.data());
    server->setNotification(notify);

    return a.exec();
}
