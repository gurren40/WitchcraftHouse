#include <QAndroidService>
#include "rep_service_source.h"

class Service : public ServiceSource {
public slots:
    // Service interface
    void ping(const QString &msg) override {
        emit pong(msg + " from server");
    }
};

int main(int argc, char *argv[])
{
    QAndroidService app(argc, argv);

    QRemoteObjectHost *srcNode = new QRemoteObjectHost(QUrl(QStringLiteral("local:replica")));
    Service service;
    if(srcNode->enableRemoting(&service)){
        qDebug() << "qwerty enabled remoting";
    }
    else {
        qDebug() << "not enabled qwerty";
    }

    return app.exec();
}
