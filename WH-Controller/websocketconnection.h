#ifndef WEBSOCKETCONNECTION_H
#define WEBSOCKETCONNECTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QWebSocket>
#include <QUrl>
#include <QDebug>

class WebsocketConnection : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketConnection(const QUrl &url, bool debug = false, QObject *parent = nullptr);

signals:
    void closed();
    void getDeviceList(QJsonObject json);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

public slots:
    void sendMessage(QJsonObject json);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // WEBSOCKETCONNECTION_H
