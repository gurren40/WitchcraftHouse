#include <QRemoteObjectHost>
#include <QCoreApplication>
#include "service.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QRemoteObjectHost srcNode(QUrl(QStringLiteral("local:replica")));
        Service service;
        srcNode.enableRemoting(&service);

    a.exec();
    return 0;
}

