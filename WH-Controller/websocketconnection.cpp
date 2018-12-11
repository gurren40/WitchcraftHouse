#include "websocketconnection.h"

QT_USE_NAMESPACE

WebsocketConnection::WebsocketConnection(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &WebsocketConnection::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebsocketConnection::closed);
    m_webSocket.open(QUrl(url));
}

void WebsocketConnection::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebsocketConnection::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void WebsocketConnection::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    //m_webSocket.close();
    QByteArray theMessage = message.toLocal8Bit();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(theMessage));
    QJsonObject jsonObj = jsonDoc.object();
    if(jsonObj["function"].toString() == "getDeviceList"){
        m_webSocket.sendTextMessage(QStringLiteral("messege recivied"));
        emit getDeviceList(jsonObj);
    }
}

void WebsocketConnection::sendMessage(QJsonObject json)
{
    QJsonDocument doc(json);
    QString message(doc.toJson());
    m_webSocket.sendTextMessage(message);
}
