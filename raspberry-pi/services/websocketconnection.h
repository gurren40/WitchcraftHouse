#ifndef WEBSOCKETCONNECTION_H
#define WEBSOCKETCONNECTION_H

#include <QObject>
#include <QWebSocket>
#include <QNetworkRequest>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTimer>
#include <QTextStream>

class WebsocketConnection : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketConnection(QObject *parent = nullptr);

signals:
    void jsonReceived(QJsonObject json);
    void pong(quint64 elapsedTime, QByteArray payload);

public slots:
    void sendJson(QJsonObject json);
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void connectLoop();
    void ping();
    void onPong(quint64 elapsedTime, QByteArray payload);

private:
    QWebSocket *m_websocket;
    QNetworkRequest m_request;
    QTimer *m_pingTimer;
    QTimer *m_disconnectTimer;
};

#endif // WEBSOCKETCONNECTION_H
