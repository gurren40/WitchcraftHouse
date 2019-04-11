#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QSettings>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    bool isOnline() const;
    bool sendMessage(QJsonObject json);

signals:
    void messageReceived(QJsonObject json);
    void websocketConnected();
    void websocketDisconnected();

public slots:
    void connectionLoop();
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void connectAuth();
    void connectControl();
    void disconnectWebsocket();
    void setPongTrue();
    void connectionKeeper();

private:
    QWebSocket* m_websocket;
    bool m_isOnline;
    QTimer *m_timer;
    QTimer *m_pingTimer;
    bool m_pong;
};

#endif // CONNECTION_H
