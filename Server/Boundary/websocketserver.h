#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

//QT library
#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QUrl>
#include <QNetworkRequest>

//library
#include "Library/QJsonWebToken/qjsonwebtoken.h"

//Controler
#include "Control/usercontroller.h"
#include "Control/devicecontroller.h"
#include "Control/schedulecontroller.h"
#include "Control/sharedcontroller.h"

class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketServer(quint16 port, QObject *parent = nullptr);
    ~WebsocketServer();

signals:
    void closed();
    void sendMail(QString sendTo, QString title, QString body);

public slots:
    void onNewConnection();
    void setDatabase(QSqlDatabase *database);
    void forceDisconnect(QWebSocket *pClient);
    void setSecret(QString secr);

    //for auth
    void authProcessTextMessage(QString message);
    void authProcessBinaryMessage(QByteArray message);
    void authSocketDisconnected();

    //for control device
    void broadcastToAllUserControlDevice(int userID, QJsonObject json);
    void controlProcessTextMessage(QString message);
    //void controlProcessBinaryMessage(QByteArray message);
    //void controlSocketDisconnected();

    //for device
    void broadcastToDevice(QUuid deviceUUID, QJsonObject json);
    //void deviceProcessTextMessage(QString message);
    //void deviceProcessBinaryMessage(QByteArray message);
    //void deviceSocketDisconnected();

    //misc
    QJsonObject getJwtPayload(QNetworkRequest request);
    void deletedControlDevice(QUuid controlDeviceID);

private:
    QWebSocketServer *m_pWebSocketServer;
    QHash<QString,QWebSocket *> m_controlDevice;
    QHash<QString,QWebSocket *> m_device;
    QList<QWebSocket *> m_auth;
    bool m_debug;
    QString secret;
    QSqlDatabase db;

    //private function
    QString getPathWithoutQuery(QUrl url);
};

#endif // WEBSOCKETSERVER_H
