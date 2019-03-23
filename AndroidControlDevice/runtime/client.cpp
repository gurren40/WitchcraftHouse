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
}

bool Client::getIsOnline() const
{
    return m_isOnline;
}

void Client::setIsOnline(bool isOnline)
{
    m_isOnline = isOnline;
    emit isOnlineChanged();
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
    emit isLoggedInChanged();
}

void Client::onTokenExpired()
{
    logOut();
}

