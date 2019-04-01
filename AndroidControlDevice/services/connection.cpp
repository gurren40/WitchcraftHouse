#include "connection.h"
#include <QDebug>

Connection::Connection(QObject *parent) : QObject(parent)
{
    m_isOnline = false;
    m_websocket = new QWebSocket;
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&Connection::connectionLoop);
    connect(m_websocket,&QWebSocket::connected,this,&Connection::onConnected);
    connect(m_websocket,&QWebSocket::disconnected,this,&Connection::onDisconnected);
    connect(m_websocket, &QWebSocket::textMessageReceived, this, &Connection::onTextMessageReceived);
    m_timer->setInterval(2000);
    m_timer->setSingleShot(true);
    connectionLoop();
}

void Connection::connectionLoop()
{
    QSettings setting;
    if(!setting.contains("jwt")){
        connectAuth();
    }
    else{
        connectControl();
    }
}

void Connection::onConnected()
{
    emit websocketConnected();
    m_isOnline = true;
}

void Connection::onDisconnected()
{
    emit websocketDisconnected();
    m_isOnline = false;
    m_timer->start();
}

void Connection::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
    QByteArray theMessage = message.toLocal8Bit();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(theMessage));
    QJsonObject jsonObj = jsonDoc.object();
    emit messageReceived(jsonObj);
}

void Connection::connectAuth()
{
    QSettings setting;
    if(!setting.contains("serverDomain")){
        onDisconnected();
    }
    else {
        QUrl url(setting.value("serverDomain").toString() + "/authentication");
        QNetworkRequest request(url);
        qDebug() << "WebSocket server authentication:" << url;
        m_websocket->open(request);
    }
}

void Connection::connectControl()
{
    QSettings setting;
    if(!setting.contains("serverDomain")){
        onDisconnected();
    }
    else {
        QUrl url(setting.value("serverDomain").toString() + "/control");
        QNetworkRequest request(url);
        request.setRawHeader("jwt",setting.value("jwt").toString().toUtf8());
        qDebug() << "WebSocket server authentication:" << url;
        m_websocket->open(request);
    }
}

void Connection::disconnectWebsocket()
{
    m_websocket->close();
}

bool Connection::isOnline() const
{
    return m_isOnline;
}

bool Connection::sendMessage(QJsonObject json)
{
    if(!m_isOnline){
        return m_isOnline;
    }
    else {
        QJsonDocument jsonDoc(json);
        m_websocket->sendTextMessage(jsonDoc.toJson());
        return m_isOnline;
    }
}
