#include <QCoreApplication>
#include <QSettings>
#include "websocketconnection.h"
#include "websocketserver.h"
#include "webservice.h"
#include "hub.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Witchcraft Hub");
    QCoreApplication::setOrganizationDomain("house.witchcraft.web.id");
    QCoreApplication::setOrganizationName("Witchcraft");

    WebsocketConnection *websocket = new WebsocketConnection;
    WebsocketServer *websocketServer = new WebsocketServer;

    Hub *hub = new Hub;
    WebService *webservice = new WebService;
    QObject::connect(websocket,&WebsocketConnection::jsonReceived,hub,&Hub::jsonReceivedFromMain);
    QObject::connect(hub,&Hub::sendJsonToMain,websocket,&WebsocketConnection::sendJson);
    QObject::connect(websocketServer,&WebsocketServer::jsonReceived,hub,&Hub::jsonReceivedFromClient);
    QObject::connect(hub,&Hub::broadcastJson,websocketServer,&WebsocketServer::sendJson);
    QObject::connect(webservice,&WebService::jsonReceived,hub,&Hub::jsonReceivedFromClient);
    QObject::connect(hub,&Hub::broadcastJson,webservice,&WebService::sendJson);

    return a.exec();
}
