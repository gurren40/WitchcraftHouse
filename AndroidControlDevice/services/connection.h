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
    void pong(int elapsedTime, QByteArray payload);

public slots:
    void connectionLoop();
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void connectAuth();
    void connectControl();
    void disconnectWebsocket();
    void doPing(QByteArray payload = "witchcraft");
    void onPong(quint64 elapsedTime, QByteArray payload);
    void onSslErrors(const QList<QSslError> &errors);

private:
    QWebSocket* m_websocket;
    bool m_isOnline;
    QTimer *m_timer;
    QTimer *m_pingTimer;
    int m_pongElapsedTime;
    int m_pongCount;
};

#endif // CONNECTION_H
