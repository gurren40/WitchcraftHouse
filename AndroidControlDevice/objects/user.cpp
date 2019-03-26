#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

bool User::isOnline() const
{
    return m_isOnline;
}

void User::setIsOnline(bool isOnline)
{
    m_isOnline = isOnline;
    emit isOnlineSig();
}

bool User::isTokenExpired() const
{
    return m_isTokenExpired;
}

void User::setIsTokenExpired(bool isTokenExpired)
{
    m_isTokenExpired = isTokenExpired;
    emit isTokenExpiredSig();
}

bool User::isLoggedIn()
{
    QSettings setting;
    if(setting.contains("jwt")){
        m_isLoggedIn = true;
    }
    else {
        m_isLoggedIn = false;
    }
    return m_isLoggedIn;
}

QString User::email()
{
    QSettings setting;
    if(setting.contains("email")){
        return setting.value("email").toString();
    }
    else{
        return "Not Set";
    }
}

void User::setEmail(const QString &email)
{
    QSettings setting;
    setting.setValue("email",email);
    emit emailSig();
}

RemoteReplica *User::remote() const
{
    return m_remote;
}

void User::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}

QString User::serverDomain()
{
    QSettings setting;
    if(setting.contains("serverDomain")){
        return setting.value("serverDomain").toString();
    }
    else{
        return "Not Set";
    }
}

void User::setServerDomain(const QString &serverDomain)
{
    QSettings setting;
    setting.setValue("serverDomain",serverDomain);
    emit serverDomainSig();
}

QString User::thisDeviceModel()
{
    QAndroidJniObject jstringValue = QAndroidJniObject::callStaticObjectMethod<jstring>("id/web/witchcraft/house/MyActivity","getDeviceModel");
    return jstringValue.toString();
}

void User::getUserInfo()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = email();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getUserInfo"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void User::requestLoginToken(QVariant email, QVariant password)
{
    QJsonObject jsonObj;
    jsonObj["email"] = email.toString();
    jsonObj["password"] = password.toString();
    jsonObj["name"] = thisDeviceModel();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["requestLoginToken"] = jsonArray;
    m_remote->sendToServer(toSend);
}

void User::createNewUser(QVariant email, QVariant name, QVariant password)
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

void User::editUser(QVariant email, QVariant name, QVariant password)
{
    QJsonObject jsonObj;
    if(email.toString() == this->email()){
        jsonObj["email"] = email.toString();
        jsonObj["password"] = password.toString();
        jsonObj["name"] = name.toString();
        QJsonArray jsonArray;
        jsonArray.append(jsonObj);
        QJsonObject toSend;
        toSend["editUser"] = jsonArray;
        m_remote->sendToServer(toSend);
    }
}

void User::setUserInfo(QJsonObject json)
{
    QJsonObject jsonObj = json.value("setUserInfo").toObject();
    if(jsonObj.value("email").toString() == email()){
        m_name = jsonObj.value("name").toString();
        emit nameSig();
    }
}

QString User::getName() const
{
    return m_name;
}

void User::setName(const QString &name)
{
    m_name = name;
    emit nameSig();
}

void User::logOut()
{
    QSettings setting;
    setting.remove("email");
    setting.remove("serverDomain");
    setting.remove("jwt");
    emit emailSig();
    emit serverDomainSig();
    emit isLoggedInSig();
    m_remote->logOut();
}

void User::getAllData()
{
    QJsonObject jsonObj;
    jsonObj["email"] = email();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getAllData"] = jsonArray;
    m_remote->sendToServer(toSend);
}
