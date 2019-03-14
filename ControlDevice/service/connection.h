#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QWebSocket>
#include <QJsonObject>
#include <QJsonDocument>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);

    QUrl url() const;
    void setUrl(const QUrl &url);

signals:
    void closed();
    void messageReceived(QJsonObject json);
    
public slots:
    void connect();
    void onConnected();
    void onTextMessageReceived(QString message);
    void sendMessage(QJsonObject message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // CONNECTION_H
