//#include <QRemoteObjectNode>
#include "backend.h"
#include "rep_service_replica.h"

Backend::Backend(QObject *parent) : QObject(parent)
{

}

void Backend::timerToCreateServer(int time)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(createServer()));
    timer->start(time);
}

void Backend::createServer()
{
    QRemoteObjectNode *repNode = new QRemoteObjectNode(this);
    if(repNode->connectToNode(QUrl(QStringLiteral("local:replica")))){
        qDebug() << "service connected";
    }
    else{
        qDebug() << "service NOT connected";
    }
    QSharedPointer<ServiceReplica> rep(repNode->acquire<ServiceReplica>());
    bool res = rep->waitForSource();
    if(res) {
        qDebug()<<"acquired";
    } else {
        qDebug()<<"NOT acquired";
    }
    //Q_ASSERT(res);
    QObject::connect(rep.data(), &ServiceReplica::pong, [](const QString &msg){
        qDebug() << msg;
    });
    rep->ping("Hello");
}
