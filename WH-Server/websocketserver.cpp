#include "websocketserver.h"

#include <cstdio>
using namespace std;

QT_USE_NAMESPACE

static QString getIdentifier(QWebSocket *peer)
{
    return QStringLiteral("%1:%2").arg(peer->peerAddress().toString(),
                                       QString::number(peer->peerPort()));
}

//konstruktor
WebsocketServer::WebsocketServer(quint16 port,QObject *parent) : QObject(parent), m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Witchcraft House Server"),QWebSocketServer::NonSecureMode,this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        QTextStream(stdout) << "Websocket Server listening on port " << port << '\n';
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebsocketServer::onNewConnection);
    }
}

WebsocketServer::~WebsocketServer(){
    m_pWebSocketServer->close();
}

//fungsi - fungsi
void WebsocketServer::onNewConnection(){
    auto pSocket = m_pWebSocketServer->nextPendingConnection();
    QTextStream(stdout) << getIdentifier(pSocket) << " connected!\n";
    pSocket->setParent(this);

    connect(pSocket, &QWebSocket::textMessageReceived,
            this, &WebsocketServer::processMessage);
    connect(pSocket, &QWebSocket::disconnected,
            this, &WebsocketServer::socketDisconnected);

    m_clients << pSocket;
}

void WebsocketServer::processMessage(const QString &message)
{
    QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    /* old stuff
    for (QWebSocket *pClient : qAsConst(m_clients)) {
        if (pClient != pSender) //don't echo message back to sender
            pClient->sendTextMessage(message);
        QTextStream(stdout) << message << '\n';
    }
    */
    QTextStream(stdout) << message << '\n';
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    if(jsonObj["toWhere"].toString() == "toDevice")
        emit toDeviceController(pSender->requestUrl(),jsonObj);
}

void WebsocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QTextStream(stdout) << getIdentifier(pClient) << " disconnected!\n";
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void WebsocketServer::sendMessageToDevice(QString uuid, QUrl url, QJsonObject json)
{
    //QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    QJsonDocument doc(json);
    QString message(doc.toJson());
    for (QWebSocket *pClient : qAsConst(m_clients)){
        if (pClient->requestUrl().path()==url.path()){
            if("/device/"+uuid == pClient->requestUrl().path()){
                pClient->sendTextMessage(message);
            }
        }
    }
}

void WebsocketServer::sendMessageToControllDevice(QUrl url, QJsonObject json)
{
    //QWebSocket *pSender = qobject_cast<QWebSocket *>(sender());
    QJsonDocument doc(json);
    QString message(doc.toJson());
    for (QWebSocket *pClient : qAsConst(m_clients)){
        if (pClient->requestUrl().path()==url.path()){
            pClient->sendTextMessage(message);
            QTextStream(stdout) << message << "\n";
        }
    }
}
