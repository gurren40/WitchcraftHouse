#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{

}

Client::Client(RemoteReplica *remote, QObject *parent) : QObject(parent)
{
    setRemote(remote);
}

RemoteReplica *Client::getRemote() const
{
    return m_remote;
}

void Client::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
    connect(m_remote,&RemoteReplica::fromServerSig,this,&Client::fromServer);
    connect(this,&Client::sendToServer,m_remote,&RemoteReplica::sendToServer); // well, you can do it directly from m_remote :3
    connect(m_remote,&RemoteReplica::setIsOnlineSig,this,&Client::setIsOnline);
    connect(m_remote,&RemoteReplica::tokenExpiredSig,this,&Client::onTokenExpired);
}

bool Client::getIsOnline() const
{
    return m_isOnline;
}

void Client::setIsOnline(bool isOnline)
{
    m_isOnline = isOnline;
    emit isOnlineChanged();
    if(getIsLoggedIn() && isOnline){
        getAllData();
    }
}

bool Client::getIsLoggedIn()
{
    QSettings setting;
    if(!setting.contains("jwt")){
        return false;
    }
    else{
        return true;
    }
}

QString Client::getUserEmail()
{
    QSettings setting;
    if(!setting.contains("email")){
        return "Not Set";
    }
    else{
        return setting.value("email").toString();
    }
}

void Client::setUserEmail(QString userEmail)
{
    QSettings setting;
    setting.setValue("email",userEmail);
}

QString Client::getServerDomain()
{
    QSettings setting;
    if(!setting.contains("serverDomain")){
        return "Not Set";
    }
    else {
        return setting.value("serverDomain").toString();
    }
}

void Client::setServerDomain(QString serverDomain)
{
    QSettings setting;
    setting.setValue("serverDomain",serverDomain);
}

void Client::logOut()
{
    QSettings setting;
    setting.remove("email");
    setting.remove("serverDomain");
    setting.remove("jwt");
    emit isLoggedInChanged();
    m_remote->logOut();
}

void Client::onTokenExpired(bool value)
{
    if(value){
        logOut();
    }
}

void Client::fromServer(QJsonObject json)
{
//    loginToken will implemented from service(?)
//    if(json.contains("LoginToken")){
//        setLoginToken();
//    }
    if(json.contains("UserInfo")){
        setUserInfo(json);
    }
    if(json.contains("deviceList")){
        setDeviceList(json);
    }
    if(json.contains("groupList")){
        setGroupList(json);
    }
    if(json.contains("pinList")){
        setPinList(json);
    }
    if(json.contains("scheduleList")){
        setScheduleList(json);
    }
    if(json.contains("sharedList")){
        setSharedList(json);
    }
    if(json.contains("sharedPinList")){
        setSharedPinList(json);
    }
    if(json.contains("settedPinValue")){
        settedPinValue(json);
    }
}

void Client::getUserInfo()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getUserInfo"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Client::getControlDeviceList()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getControlDeviceList"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Client::requestLoginToken(QVariant email, QVariant password)
{
    QJsonObject jsonObj;
    jsonObj["email"] = email.toString();
    jsonObj["password"] = password.toString();
    jsonObj["name"] = getDeviceModel();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["requestLoginToken"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Client::createNewUser(QVariant email, QVariant name, QVariant password)
{
    QJsonObject jsonObj;
    jsonObj["email"] = email.toString();
    jsonObj["password"] = password.toString();
    jsonObj["name"] = name.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["createNewUser"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Client::editUser(QVariant email, QVariant name, QVariant password)
{
    QJsonObject jsonObj;
    jsonObj["email"] = email.toString();
    jsonObj["password"] = password.toString();
    jsonObj["name"] = name.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["editUser"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void Client::deleteControlDevice(QVariant controlDeviceID)
{
    QJsonObject jsonObj;
    jsonObj["controlDeviceID"] = controlDeviceID.toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteControlDevice"] = jsonArray;
    m_remote->sendToServer(toSend);
}

