#include "connection.h"
#include <QDebug>

Connection::Connection(QObject *parent) : QObject(parent)
{
    m_isOnline = false;
    m_pongCount = 0;
    m_websocket = new QWebSocket;
    m_timer = new QTimer(this);
    m_pingTimer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&Connection::connectionLoop);
    connect(m_pingTimer,SIGNAL(timeout()),this,SLOT(doPing()));
    connect(m_websocket,&QWebSocket::pong,this,&Connection::onPong);
    connect(m_websocket,&QWebSocket::connected,this,&Connection::onConnected);
    connect(m_websocket,&QWebSocket::disconnected,this,&Connection::onDisconnected);
    connect(m_websocket,&QWebSocket::textMessageReceived, this, &Connection::onTextMessageReceived);
    m_timer->setInterval(500);
    m_timer->setSingleShot(true);
    m_pingTimer->setInterval(5000);
    m_pingTimer->setSingleShot(false);
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
    m_pongCount = 0;
    m_pingTimer->start();
}

void Connection::onDisconnected()
{
    emit websocketDisconnected();
    m_isOnline = false;
    m_pingTimer->stop();
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
    if(!setting.value("isLocalDomain").toBool()){
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
    else{
        if(!setting.contains("localDomain")){
            onDisconnected();
        }
        else {
            QUrl url(setting.value("localDomain").toString() + "/authentication");
            QNetworkRequest request(url);
            qDebug() << "WebSocket server authentication:" << url;
            m_websocket->open(request);
        }
    }
}

void Connection::connectControl()
{
    QSettings setting;
    if(!setting.value("isLocalDomain").toBool()){
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
    else {
        if(!setting.contains("localDomain")){
            onDisconnected();
        }
        else {
            QUrl url(setting.value("localDomain").toString() + "/control");
            QNetworkRequest request(url);
            request.setRawHeader("jwt",setting.value("jwt").toString().toUtf8());
            qDebug() << "WebSocket server authentication:" << url;
            m_websocket->open(request);
        }
    }
}

void Connection::disconnectWebsocket()
{
    m_websocket->close();
}

void Connection::doPing(QByteArray payload)
{
    if(m_pongCount <= 10){
        m_websocket->ping(payload);
    }
    else if(m_pongCount > 10){
        disconnectWebsocket();
    }
}

void Connection::onPong(quint64 elapsedTime, QByteArray payload)
{
    int intElapsedTime = QString::number(elapsedTime).toInt();
    m_pongCount = 0;
    emit pong(intElapsedTime,payload);
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
