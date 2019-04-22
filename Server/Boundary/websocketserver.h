#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

//QT library
#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>

//library
#include "Library/QJsonWebToken/qjsonwebtoken.h"

//Controler
#include "Control/usercontroller.h"
#include "Control/devicecontroller.h"
#include "Control/schedulecontroller.h"
#include "Control/sharedcontroller.h"

//cron scheduler
#include "Boundary/cronscheduler.h"

class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketServer(quint16 port, QObject *parent = nullptr);
    ~WebsocketServer();

    void setCronScheduler(CronScheduler *value);
    void setUC(UserController *UC);
    void setDC(DeviceController *DC);
    void setSC(ScheduleController *SC);
    void setShC(SharedController *ShC);

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
    void controlProcessBinaryMessage(QByteArray message);
    void controlSocketDisconnected();
    void disconnectControlDevice(QString stringUUID);

    //for device
    void broadcastToDevice(QUuid deviceUUID, QJsonObject json);
    void deviceProcessTextMessage(QString message);
    void deviceProcessBinaryMessage(QByteArray message);
    void deviceSocketDisconnected();
    void deletedDevice(QUuid deviceUUID);
    void setPinValueFromCron(QJsonObject json, int userID);
    void disconnectDevice(QString stringUUID);

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

    //Cron Scheduler
    CronScheduler *cronScheduler;

    //Controler
    UserController *m_UC;
    DeviceController *m_DC;
    ScheduleController *m_SC;
    SharedController *m_ShC;

    //private function
    QString getPathWithoutQuery(QUrl url);
};

#endif // WEBSOCKETSERVER_H
