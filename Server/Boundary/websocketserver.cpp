#include "websocketserver.h"

WebsocketServer::WebsocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
    QWebSocketServer::NonSecureMode, this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            QTextStream(stdout) << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebsocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebsocketServer::closed);
    }
}

WebsocketServer::~WebsocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_controlDevice.begin(), m_controlDevice.end());
    qDeleteAll(m_device.begin(), m_device.end());
    qDeleteAll(m_auth.begin(), m_auth.end());
}

void WebsocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    QNetworkRequest request = pSocket->request();
    QUrl url = request.url();
    QJsonObject jwt = getJwtPayload(request);
    UserController UC(&db);
    DeviceController DC(&db);

    if(url.path() == "/authentication"){
        m_auth << pSocket;
        QTextStream(stdout) << "an application want to authenticate : " << pSocket << "\n";
        connect(pSocket, &QWebSocket::textMessageReceived, this, &WebsocketServer::authProcessTextMessage);
        connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebsocketServer::authProcessBinaryMessage);
        connect(pSocket, &QWebSocket::disconnected, this, &WebsocketServer::authSocketDisconnected);
    }
    else if(url.path() == "/control"){
        QString header = "jwt";
        if(!request.hasRawHeader(header.toUtf8())){
            forceDisconnect(pSocket);
        }
        else {
            QString token = QString::fromUtf8(request.rawHeader(header.toUtf8()));
            if(!UC.isJwtValid(jwt,url.path())){
                QJsonObject response;
                QJsonArray errorArray;
                QJsonObject error;
                error["error"] = "Tokeh has expired or deleted, please re-login with your account";
                error["errorCode"] = "4";
                errorArray.append(error);
                response["error"] = errorArray;
                QJsonDocument responseDoc(response);
                pSocket->sendTextMessage(responseDoc.toJson());
                forceDisconnect(pSocket);
            }
            else {
                m_controlDevice.insert(jwt["jti"].toString(),pSocket);
                QTextStream(stdout) << "a control device is connected : " << pSocket << "\n";
                connect(pSocket, &QWebSocket::textMessageReceived, this, &WebsocketServer::controlProcessTextMessage);
                //connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebsocketServer::controlProcessBinaryMessage);
                //connect(pSocket, &QWebSocket::disconnected, this, &WebsocketServer::controlSocketDisconnected);
            }
        }
    }
    else if(url.path() == "/device"){
        QString header = "jwt";
        if(!request.hasRawHeader(header.toUtf8())){
            forceDisconnect(pSocket);
        }
        else {
            QString token = QString::fromUtf8(request.rawHeader(header.toUtf8()));
            if(!DC.isJwtValid(jwt,url.path())){
                QJsonObject response;
                QJsonArray errorArray;
                QJsonObject error;
                error["error"] = "Tokeh has expired or deleted, please re-login with your account";
                error["errorCode"] = "4";
                errorArray.append(error);
                response["error"] = errorArray;
                QJsonDocument responseDoc(response);
                pSocket->sendTextMessage(responseDoc.toJson());
                forceDisconnect(pSocket);
            }
            else {
                m_device.insert(jwt["jti"].toString(),pSocket);
                QTextStream(stdout) << "a device is connected : " << pSocket << "\n";
                //connect(pSocket, &QWebSocket::textMessageReceived, this, &WebsocketServer::deviceProcessTextMessage);
                //connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebsocketServer::deviceProcessBinaryMessage);
                //connect(pSocket, &QWebSocket::disconnected, this, &WebsocketServer::deviceSocketDisconnected);
            }
        }
    }
    else {
        forceDisconnect(pSocket);
    }
}

void WebsocketServer::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

void WebsocketServer::forceDisconnect(QWebSocket *pClient)
{
    QTextStream(stdout) << "socketDisconnected:" << pClient;
    pClient->close();
    pClient->deleteLater();
}

void WebsocketServer::setSecret(QString secr)
{
    this->secret = secr;
}

void WebsocketServer::authProcessTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    //QJsonObject jwt = getJwtPayload(pClient->request());
    UserController UC(&db);
    UC.setSecret(secret);

    //connect signal lol
    connect(&UC,SIGNAL(sendMail(QString,QString,QString)),this,SIGNAL(sendMail(QString,QString,QString)));

    QTextStream(stdout) << jsonDoc.toJson();

    if(jsonObj.contains("createNewUser")){
        QJsonObject response = UC.createUser(jsonObj);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("requestLoginToken")){
        QJsonObject response = UC.requestLoginToken(jsonObj);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
}

void WebsocketServer::authProcessBinaryMessage(QByteArray message)
{
    QTextStream(stdout) << message;
}

void WebsocketServer::authSocketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QTextStream(stdout) << "socketDisconnected:" << pClient;
    if (pClient) {
        m_auth.removeAll(pClient);
        pClient->deleteLater();
    }
}

void WebsocketServer::broadcastToAllUserControlDevice(int userID, QJsonObject json)
{
    UserController UC(&db);

    //inisialisasi list control device
    QJsonObject cdList = UC.selectAllControlDevice(userID);
    QJsonArray array = cdList["controlDevice"].toArray();
    QJsonDocument doc(json);

    for (int i = 0;i<cdList.size();i++) {
        QJsonObject cDevice = array[i].toObject();
        if(cDevice["isControlDeviceOnline"].toBool()){
            m_controlDevice.value(cDevice["controlDeviceID"].toString())->sendTextMessage(doc.toJson());
        }
    }
}

void WebsocketServer::controlProcessTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();
    //QJsonObject jwt = getJwtPayload(pClient->request());
    UserController UC(&db);
    UC.setSecret(secret);

    //connect signal lol
    connect(&UC,SIGNAL(sendMail(QString,QString,QString)),this,SIGNAL(sendMail(QString,QString,QString)));

    QTextStream(stdout) << jsonDoc.toJson();

    if(jsonObj.contains("createNewUser")){
        QJsonObject response = UC.createUser(jsonObj);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("requestLoginToken")){
        QJsonObject response = UC.requestLoginToken(jsonObj);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
}

void WebsocketServer::broadcastToDevice(QUuid deviceUUID, QJsonObject json)
{
    QJsonDocument jsonDoc(json);
    m_device.value(deviceUUID.toString(QUuid::WithoutBraces))->sendTextMessage(jsonDoc.toJson());
}

QJsonObject WebsocketServer::getJwtPayload(QNetworkRequest request)
{
    QString header = "jwt";
    QString token = QString::fromUtf8(request.rawHeader(header.toUtf8()));
    QJsonWebToken jwt = QJsonWebToken::fromTokenAndSecret(token,secret);
    QJsonObject jsonObj = jwt.getPayloadJDoc().object();
    return  jsonObj;
}

void WebsocketServer::deletedControlDevice(QUuid controlDeviceID)
{
    m_controlDevice.value(controlDeviceID.toString(QUuid::WithoutBraces))->close();
}

QString WebsocketServer::getPathWithoutQuery(QUrl url)
{
    return QUrl(url.toString(QUrl::RemoveQuery)).path();
}
