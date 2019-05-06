#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QHash>
#include <QByteArray>
#include <QWebSocket>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QSettings>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class WebsocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketServer(QObject *parent = nullptr);

signals:
    void jsonReceived(QJsonObject json);
    void closed();

public slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void sendJson(QJsonObject json);

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // WEBSOCKETSERVER_H
