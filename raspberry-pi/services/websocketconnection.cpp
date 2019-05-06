#include "websocketconnection.h"

WebsocketConnection::WebsocketConnection(QObject *parent) : QObject(parent)
{
    QSettings setting;

    QString websocketServerUrl;
    QString deviceToken;

    if(setting.contains("websocketServerUrl")){
        websocketServerUrl = setting.value("websocketServerUrl").toString();
    }
    else{
        websocketServerUrl = "ws://192.168.0.13:9000/device";
        setting.setValue("websocketServerUrl",websocketServerUrl);
    }

    if(setting.contains("deviceToken")){
        deviceToken = setting.value("deviceToken").toString();
    }
    else{
        deviceToken = "none";
        setting.setValue("deviceToken",deviceToken);
    }

    m_websocket = new QWebSocket;
    m_request = QNetworkRequest(websocketServerUrl);
    m_request.setRawHeader("jwt",deviceToken.toUtf8());
    //m_websocket->open(m_request);

    m_disconnectTimer = new QTimer(this);
    m_disconnectTimer->setInterval(5000);
    m_disconnectTimer->setSingleShot(true);

    m_pingTimer = new QTimer(this);
    m_pingTimer->setInterval(5000);
    m_pingTimer->setSingleShot(false);
    m_pingTimer->stop();

    connect(m_websocket,&QWebSocket::connected,this,&WebsocketConnection::onConnected);
    connect(m_websocket,&QWebSocket::disconnected,this,&WebsocketConnection::onDisconnected);
    connect(m_websocket,&QWebSocket::textMessageReceived,this,&WebsocketConnection::onTextMessageReceived);
    connect(m_websocket,&QWebSocket::pong,this,&WebsocketConnection::onPong);
    connect(m_disconnectTimer,&QTimer::timeout,this,&WebsocketConnection::connectLoop);
    connect(m_pingTimer,&QTimer::timeout,this,&WebsocketConnection::ping);
    m_disconnectTimer->start();
}

void WebsocketConnection::sendJson(QJsonObject json)
{
    QJsonDocument doc(json);
    m_websocket->sendTextMessage(doc.toJson());
}

void WebsocketConnection::onConnected()
{
    m_disconnectTimer->stop();
    m_pingTimer->start();
}

void WebsocketConnection::onDisconnected()
{
    m_disconnectTimer->start();
    m_pingTimer->stop();
}

void WebsocketConnection::onTextMessageReceived(QString message)
{
    QJsonDocument doc(QJsonDocument::fromJson(message.toUtf8()));
    emit jsonReceived(doc.object());
}

void WebsocketConnection::connectLoop()
{
    m_websocket->open(m_request);
}

void WebsocketConnection::ping()
{
    m_websocket->ping("witchcraft");
}

void WebsocketConnection::onPong(quint64 elapsedTime, QByteArray payload)
{
    QTextStream(stdout) << "\nElapsed Time : " << elapsedTime;
    QTextStream(stdout) << "\nPayload : " << payload;
    emit pong(elapsedTime,payload);
}
