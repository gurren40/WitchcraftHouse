#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    //m_messageQueue = new QVector<QJsonObject>;
    m_isOnline = false;
    m_connection = new Connection(this);
    m_notification = new Notification(this);
    m_notification->setJavaClass("id/web/witchcraft/house/MyService");
    connect(m_connection,&Connection::messageReceived,this,&Server::onMessageReceived);
    connect(m_connection,&Connection::websocketConnected,this,&Server::isOnline);
    connect(m_connection,&Connection::websocketDisconnected,this,&Server::isOffline);
    connect(m_connection,&Connection::pong,this,&Server::onPong);
}

RemoteReplica *Server::remote() const
{
    return m_remote;
}

void Server::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
    //send from activity to service/server
    connect(m_remote,&RemoteReplica::sendToServerSig,this,&Server::sentToServer);

    //if token expired please notify
    //connect(this,&Server::tokenExpired,m_remote,&RemoteReplica::tokenExpired);

    //logout to reconnect
    connect(m_remote,&RemoteReplica::logOutSig,this,&Server::logOut);

    //variant
    //connect(m_remote,&RemoteReplica::sendToServerVariantSig,this,&Server::sentToServerVariant);

    //init activity
    connect(m_remote,&RemoteReplica::initActivitySig,this,&Server::initActivity);

    //ping
    connect(m_remote,&RemoteReplica::pingSig,this,&Server::onPing);

    //reconnect
    connect(m_remote,&RemoteReplica::reconnectSig,this,&Server::onReconnect);
}

void Server::sentToServer(QVariant jvar)
{
    QJsonObject json = variantToJson(jvar);
    bool isValid = m_connection->sendMessage(json);
    if(!isValid){
        m_remote->setIsOnline(false);
    }
//    m_messageQueue->append(json);
}

void Server::onMessageReceived(QJsonObject json)
{
    QSettings setting;
    int notificationID;
    if(json.contains("notification")){
        if(!setting.contains("notificationID")){
            setting.setValue("notificationID",1);
            notificationID = 0;
        }
        else {
            notificationID = setting.value("notificationID").toInt();
            setting.setValue("notificationID",notificationID + 1);
        }
        QJsonArray jsonArray = json["notification"].toArray();
        if(!jsonArray.isEmpty()){
            for (int i = 0;i<jsonArray.size();i++) {
                QJsonObject jsonObj = jsonArray.at(i).toObject();
                if(jsonObj.contains("title")){
                    m_notification->sendNotification(notificationID,jsonObj.value("title").toString(),jsonObj.value("description").toString());
                }
            }
        }
    }
    if(json.contains("error")){
        QJsonArray jsonArray = json["error"].toArray();
        for (int j = 0;j<jsonArray.size();j++) {
            QJsonObject error;
            //error["error"] = "Token has expired or deleted, please re-login with your account";
            if(error["errorCode"].toString() == "4"){
                m_remote->tokenExpired(true);
            }
        }
    }
    if(json.contains("loginToken")){
        QSettings setting;
        QJsonObject jsonObj = json.value("loginToken").toObject();
        setting.setValue("email",jsonObj.value("email").toString());
        setting.setValue("jwt",jsonObj.value("token").toString());
        m_connection->disconnectWebsocket();
    }
    if(json.contains("pinList")){
        m_pinList = json.value("pinList").toArray();
    }
    if(json.contains("settedPinValue")){
        QJsonArray jsonArray = json.value("settedPinValue").toArray();
        for (int i=0;i<jsonArray.size();i++) {
            QJsonObject jsonObj = jsonArray.at(i).toObject();
            QString title = "Pin State Changed";
            QString body;
//            if(!setting.contains("notificationID")){
//                setting.setValue("notificationID",1);
//                notificationID = 0;
//            }
//            else {
//                notificationID = setting.value("notificationID").toInt();
//                setting.setValue("notificationID",notificationID + 1);
//            }
            for (int j=0;j<m_pinList.size();j++) {
                QJsonObject jsonPinList = m_pinList.at(j).toObject();
                if(jsonPinList.value("UUID").toString() == jsonObj.value("UUID").toString()){
                    body = "Pin "+jsonPinList.value("pinName").toString()+" is set to "+jsonObj["value"].toString();
                    m_notification->sendNotification(jsonPinList.value("pinID").toInt(),title,body);
                }
            }
        }
    }
    QVariant jvar = jsonToVariant(json);
    m_remote->fromServer(jvar);
}

void Server::logOut()
{
    m_connection->disconnectWebsocket();
}

QVariant Server::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject Server::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}

void Server::isOnline()
{
    m_remote->setIsOnline(true);
    m_isOnline = true;
}

void Server::isOffline()
{
    m_remote->setIsOnline(false);
    m_isOnline = false;
}

void Server::initActivity()
{
    m_remote->setIsOnline(m_isOnline);
}

void Server::onPong(int elapsedTime, QByteArray payload)
{
    m_remote->pong(elapsedTime,payload);
//    if(m_messageQueue->size()>0){
//        for (int i = 0;i<m_messageQueue->size();i++) {
//            m_connection->sendMessage(m_messageQueue->at(i));
//        }
//        m_messageQueue->clear();
//    }
}

void Server::onPing(QByteArray payload)
{
    m_connection->doPing(payload);
}

void Server::onReconnect()
{
    m_connection->disconnectWebsocket();
}
