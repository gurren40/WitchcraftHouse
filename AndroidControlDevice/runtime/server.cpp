#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    m_connection = new Connection(this);
    m_notification = new Notification(this);
    m_notification->setJavaClass("id/web/witchcraft/house/MyService");
    connect(m_connection,&Connection::messageReceived,this,&Server::onMessageReceived);
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

    //signal if device is online / connected to websocket server
    QSignalMapper *signalMapper1 = new QSignalMapper;
    connect(m_connection,SIGNAL(websocketConnected),signalMapper1,SLOT(map()));
    signalMapper1->setMapping(m_connection,true);
    connect(signalMapper1,SIGNAL(mapped(bool)),m_remote,SLOT(setIsOnline(bool)));

    QSignalMapper *signalMapper2 = new QSignalMapper;
    connect(m_connection,SIGNAL(websocketDisconnected),signalMapper2,SLOT(map()));
    signalMapper2->setMapping(m_connection,false);
    connect(signalMapper2,SIGNAL(mapped(bool)),m_remote,SLOT(setIsOnline(bool)));

    //if token expired please notify
    //connect(this,&Server::tokenExpired,m_remote,&RemoteReplica::tokenExpired);

    //logout to reconnect
    connect(m_remote,&RemoteReplica::logOutSig,this,&Server::logOut);
}

void Server::sentToServer(QJsonObject json)
{
    bool isValid = m_connection->sendMessage(json);
    if(!isValid){
        m_remote->setIsOnline(false);
    }
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
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObj = jsonArray.at(i).toObject();
            m_notification->sendNotification(notificationID,jsonObj.value("title").toString(),jsonObj.value("description").toString());
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
            if(!setting.contains("notificationID")){
                setting.setValue("notificationID",1);
                notificationID = 0;
            }
            else {
                notificationID = setting.value("notificationID").toInt();
                setting.setValue("notificationID",notificationID + 1);
            }
            for (int j=0;j<m_pinList.size();j++) {
                QJsonObject jsonPinList = m_pinList.at(j).toObject();
                if(jsonPinList.value("UUID").toString() == jsonObj.value("UUID").toString()){
                    body = "Pin "+jsonPinList.value("pinName").toString()+" is set to "+jsonObj["value"].toString();
                    m_notification->sendNotification(notificationID,title,body);
                }
            }
        }
    }
    m_remote->fromServer(json);
}

void Server::logOut()
{
    m_connection->disconnectWebsocket();
}
