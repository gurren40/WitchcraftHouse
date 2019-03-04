#include "websocketserver.h"

WebsocketServer::WebsocketServer(quint16 port, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
    QWebSocketServer::NonSecureMode, this))
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            QTextStream(stdout) << "Echoserver listening on port : " << port;
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
                connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebsocketServer::controlProcessBinaryMessage);
                connect(pSocket, &QWebSocket::disconnected, this, &WebsocketServer::controlSocketDisconnected);
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
                connect(pSocket, &QWebSocket::textMessageReceived, this, &WebsocketServer::deviceProcessTextMessage);
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
    //inisialisasi sender
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    //inisialisasi pesan
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    //ubah pesan menjadi json object
    QJsonObject jsonObj = jsonDoc.object();
    //inisialisasi jwt payload
    QJsonObject jwt = getJwtPayload(pClient->request());
    //ambil userID berdasarkan jwt
    QUuid controlDeviceID = QUuid::fromString(jwt["jti"].toString());

    //inisialisasi kontroler
    UserController UC(&db);
    DeviceController DC(&db);
    ScheduleController SC(&db);
    SharedController ShC(&db);
    UC.setSecret(secret);
    DC.setSecret(secret);

    int userID = UC.getUserIDByControlDeviceID(controlDeviceID);

    //connect signal lol
    connect(&UC,SIGNAL(sendMail(QString,QString,QString)),this,SIGNAL(sendMail(QString,QString,QString)));
    connect(&DC,SIGNAL(sendMail(QString,QString,QString)),this,SIGNAL(sendMail(QString,QString,QString)));
    //connect(&SC,SIGNAL(sendMail(QString,QString,QString)),this,SIGNAL(sendMail(QString,QString,QString)));
    //connect(&ShC,SIGNAL(sendMail(QString,QString,QString)),this,SIGNAL(sendMail(QString,QString,QString)));
    connect(&DC,SIGNAL(broadcastToDevice(QUuid,QJsonObject)),this,SLOT(broadcastToDevice(QUuid,QJsonObject)));
    connect(&DC,SIGNAL(deletedDevice),this,SLOT(deletedDevice()));
    connect(&SC,SIGNAL(createNewCron(QUuid, QString, QUuid, QString, int)),cronScheduler,SLOT(createNewCron(QUuid, QString, QUuid, QString, int)));
    connect(&SC,SIGNAL(editCron(QUuid, QString, QUuid, QString)),cronScheduler,SLOT(editCron(QUuid, QString, QUuid, QString)));
    connect(&SC,SIGNAL(deleteCron(QUuid)),cronScheduler,SLOT(deleteCron(QUuid)));
    connect(&DC,SIGNAL(deletedPin(QUuid,int)),&SC,SLOT(deletedPin(QUuid,int)));
    connect(&DC,SIGNAL(deletedPin(QUuid,int)),&ShC,SLOT(deletedPin(QUuid,int)));
    connect(&DC,SIGNAL(deletedGroup(int,int)),&ShC,SLOT(deletedGroup(int,int)));

    QTextStream(stdout) << jsonDoc.toJson();

    //create
    if(jsonObj.contains("createNewDevice")){
        QJsonObject response = DC.createNewDevice(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getDeviceList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("createNewGroup")){
        QJsonObject response = DC.createNewGroup(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getGroupList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("createNewPin")){
        QJsonObject response = DC.createNewPin(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getPinList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("createNewSchedule")){
        QJsonObject response = SC.createNewSchedule(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = SC.getScheduleList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("createNewShared")){
        QJsonObject response = ShC.createNewShared(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = ShC.getSharedList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }

    //edit
    if(jsonObj.contains("editUser")){
        QJsonObject response = UC.editUser(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = UC.getUserInfo(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("editDevice")){
        QJsonObject response = DC.editDevice(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getDeviceList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("editGroup")){
        QJsonObject response = DC.editGroup(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getGroupList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("editPin")){
        QJsonObject response = DC.editPin(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getPinList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("editSchedule")){
        QJsonObject response = SC.editSchedule(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = SC.getScheduleList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("editShared")){
        QJsonObject response = ShC.editShared(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = ShC.getSharedList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }

    //delete
    if(jsonObj.contains("deleteDevice")){
        QJsonObject response = DC.deleteDevice(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getDeviceList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("deleteGroup")){
        QJsonObject response = DC.deleteGroup(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getGroupList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("deletePin")){
        QJsonObject response = DC.deletePin(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = DC.getPinList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("deleteSchedule")){
        QJsonObject response = SC.deleteSchedule(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = SC.getScheduleList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }
    if(jsonObj.contains("deleteShared")){
        QJsonObject response = ShC.deleteShared(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
        QJsonObject response2 = ShC.getSharedList(userID);
        broadcastToAllUserControlDevice(userID,response2);
    }

    //get list
    if(jsonObj.contains("getUserInfo")){
        QJsonObject response = UC.getUserInfo(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getDeviceList")){
        QJsonObject response = DC.getDeviceList(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getGroupList")){
        QJsonObject response = DC.getGroupList(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getPinList")){
        QJsonObject response = DC.getPinList(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getScheduleList")){
        QJsonObject response = SC.getScheduleList(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getSharedList")){
        QJsonObject response = ShC.getSharedList(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getSharedPinList")){
        QJsonObject response = ShC.getSharedPinList(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getAllData")){
        QJsonObject response = UC.getAllDatalist(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
    if(jsonObj.contains("getControlDeviceList")){
        QJsonObject response = UC.getControlDeviceList(userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }

    //set pin value
    if(jsonObj.contains("setPinValue")){
        QJsonObject response = DC.setPinValue(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
}

void WebsocketServer::controlProcessBinaryMessage(QByteArray message)
{
    QTextStream(stdout) << message;
}

void WebsocketServer::controlSocketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QTextStream(stdout) << "socketDisconnected:" << pClient;
    QJsonObject jwtPayload = getJwtPayload(pClient->request());
    if (pClient) {
        m_controlDevice.remove(jwtPayload["jti"].toString());
        pClient->deleteLater();
    }
}

void WebsocketServer::broadcastToDevice(QUuid deviceUUID, QJsonObject json)
{
    QJsonDocument jsonDoc(json);
    m_device.value(deviceUUID.toString(QUuid::WithoutBraces))->sendTextMessage(jsonDoc.toJson());
}

void WebsocketServer::deviceProcessTextMessage(QString message)
{
    //inisialisasi sender
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    //inisialisasi pesan
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
    //ubah pesan menjadi json object
    QJsonObject jsonObj = jsonDoc.object();
    //inisialisasi jwt payload
    QJsonObject jwt = getJwtPayload(pClient->request());
    //ambil userID berdasarkan jwt
    QUuid DeviceUUID = QUuid::fromString(jwt["jti"].toString());

    //inisialisasi kontroler
    DeviceController DC(&db);
    int userID = DC.getUserIDByDeviceID(DeviceUUID);

    connect(&DC,SIGNAL(broadcastToAllUserControlDevice(int,QJsonObject)),this,SLOT(broadcastToAllUserControlDevice(int,QJsonObject)));

    if(jsonObj.contains("settedPinValue")){
        QJsonObject response = DC.settedPinValue(jsonObj,userID);
        QJsonDocument toSend(response);
        pClient->sendTextMessage(toSend.toJson());
    }
}

void WebsocketServer::deletedDevice(QUuid deviceUUID)
{
    m_device.value(deviceUUID.toString(QUuid::WithoutBraces))->close();
}

void WebsocketServer::setPinValueFromCron(QJsonObject json, int userID)
{
    DeviceController DC(&db);
    connect(&DC,SIGNAL(broadcastToDevice(QUuid,QJsonObject)),this,SLOT(broadcastToDevice(QUuid,QJsonObject)));

    DC.setPinValue(json,userID);
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

void WebsocketServer::setCronScheduler(CronScheduler *value)
{
    cronScheduler = value;
    connect(cronScheduler,SIGNAL(setPinValue(QJsonObject,int)),this,SLOT(setPinValueFromCron(QJsonObject,int)));
}

QString WebsocketServer::getPathWithoutQuery(QUrl url)
{
    return QUrl(url.toString(QUrl::RemoveQuery)).path();
}
