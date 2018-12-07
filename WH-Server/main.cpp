#include <QCoreApplication>

#include "websocketserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WebsocketServer server(1234);

    return a.exec();
}
