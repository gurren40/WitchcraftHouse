#include "connection.h"

Connection::Connection(QObject *parent) : QObject(parent)
{
    QObject::connect(&m_webSocket, &QWebSocket::connected, this, &Connection::onConnected);
    QObject::connect(&m_webSocket, &QWebSocket::disconnected, this, &Connection::closed);
}

QUrl Connection::url() const
{
    return m_url;
}

void Connection::setUrl(const QUrl &url)
{
    m_url = url;
}

void Connection::connect()
{
    m_webSocket.open(m_url);
}

void Connection::onConnected()
{
    QObject::connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Connection::onTextMessageReceived);
}

void Connection::onTextMessageReceived(QString message)
{
    QJsonDocument messageDoc = QJsonDocument::fromJson(message.toUtf8());
    emit messageReceived(messageDoc.object());
}

void Connection::sendMessage(QJsonObject message)
{
    QJsonDocument messageDoc(message);
    m_webSocket.sendTextMessage(messageDoc.toJson());
}
