#include "websocketserver.h"

WebsocketServer::WebsocketServer(QObject *parent) : QObject(parent)
{
    QSettings setting;
    quint16 port;
    if(setting.contains("serverport")){
        port = setting.value("serverport").toInt();
    }
    else{
        port = 1234;
        setting.setValue("serverport",port);
    }
    m_pWebSocketServer = new QWebSocketServer(QStringLiteral("Hub Server"), QWebSocketServer::NonSecureMode, this);
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Hub Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,this, &WebsocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebsocketServer::closed);
    }
}

void WebsocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebsocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebsocketServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebsocketServer::socketDisconnected);

    m_clients << pSocket;
    QTextStream(stdout) << "\n" << pSocket << "is connected\n";
}

void WebsocketServer::processTextMessage(QString message)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(message.toUtf8());
    emit jsonReceived(jdoc.object());
    QTextStream(stdout) << "\n" << jdoc.toJson()<< "\n";
}

void WebsocketServer::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void WebsocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient) {
        QTextStream(stdout) << "\n" << pClient<< "is disconnected\n";
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void WebsocketServer::sendJson(QJsonObject json)
{
    QJsonDocument doc(json);
    for (int i = 0;i<m_clients.size();i++) {
        m_clients.at(i)->sendTextMessage(doc.toJson());
        QTextStream(stdout) << "\n" << doc.toJson()<< "\n";
    }
}
