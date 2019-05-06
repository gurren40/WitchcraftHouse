#include <QCoreApplication>
#include <QSettings>
#include "thermostat.h"
#include "websocketconnection.h"
#include <wiringPi.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Witchcraft Thermostat");
    QCoreApplication::setOrganizationDomain("house.witchcraft.web.id");
    QCoreApplication::setOrganizationName("Witchcraft");

    if ( wiringPiSetup() == -1 ) exit( 1 );
    WebsocketConnection *websocket = new WebsocketConnection;
    Thermostat *thermostat = new Thermostat;
    QObject::connect(websocket,&WebsocketConnection::jsonReceived,thermostat,&Thermostat::jsonReceived);
    QObject::connect(thermostat,&Thermostat::sendJson,websocket,&WebsocketConnection::sendJson);
    return a.exec();
}
