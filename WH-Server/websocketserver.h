#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QList>
#include <QtWebSockets>
#include <QJsonObject>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)
QT_FORWARD_DECLARE_CLASS(QString)

class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketServer(quint16 port, QObject *parent = nullptr);
    virtual ~WebsocketServer();

signals:
    void toDeviceController(QUrl url, QJsonObject json);
    void toSharedController(QUrl url, QJsonObject json);
    void toAccountController(QUrl url, QJsonObject json);
    void toScheduleController(QUrl url, QJsonObject json);

    void sendToDeviceError(QString whatError, QJsonObject json);
    void sendToControllDeviceError(QString whatError, QJsonObject json);

public slots:
    void onNewConnection();
    void processMessage(const QString &message);
    void socketDisconnected();
    void sendMessageToDevice(QString uuid, QUrl url, QJsonObject json);
    void sendMessageToControllDevice(QUrl url, QJsonObject json);

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // WEBSOCKETSERVER_H
