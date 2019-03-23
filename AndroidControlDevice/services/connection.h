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

public slots:
    void connectionLoop();
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
    void connectAuth();
    void connectControl();

private:
    QWebSocket* m_websocket;
    bool m_isOnline;
    QTimer *m_timer;
    QSettings *m_setting;
};

#endif // CONNECTION_H
