#include "user.h"

User::User(QObject *parent) : QObject(parent)
{
    m_deviceModel = "unknown";
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

bool User::isLocalDomain()
{
    QSettings setting;
    if(setting.contains("isLocalDomain")){
        return setting.value("isLocalDomain").toBool();
    }
    else{
        setting.setValue("isLocalDomain",false);
        return setting.value("isLocalDomain").toBool();
    }
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
    connect(m_remote,&RemoteReplica::pongSig,this,&User::onPong);
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

QString User::localDomain()
{
    QSettings setting;
    if(setting.contains("localDomain")){
        return setting.value("localDomain").toString();
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

void User::setLocalDomain(const QString &localDomain)
{
    QSettings setting;
    setting.setValue("localDomain",localDomain);
    emit localDomainSig();
}

void User::setIsLocalDomain(bool value)
{
    QSettings setting;
    setting.setValue("isLocalDomain",value);
    emit isLocalDomainSig();
    m_remote->reconnect();
}

QString User::thisDeviceModel()
{
//    QAndroidJniObject jstringValue = QAndroidJniObject::callStaticObjectMethod<jstring>("id/web/witchcraft/house/MyActivity","getDeviceModel");
//    return jstringValue.toString();
    return m_deviceModel;
}

QString User::getJwt()
{
    QSettings setting;
    if(setting.contains("jwt")){
        return setting.value("jwt").toString();
    }
    else{
        return "Not Yet Avaiable";
    }
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
    m_remote->sendToServer(jsonToVariant(toSend));
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
    m_remote->sendToServer(jsonToVariant(toSend));
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
    m_remote->sendToServer(jsonToVariant(toSend));
}

void User::editUser(QVariant email, QVariant name, QVariant oldPassword, QVariant newPassword)
{
    QJsonObject jsonObj;
    if(email.toString() == this->email()){
        jsonObj["email"] = email.toString();
        jsonObj["oldPassword"] = oldPassword.toString();
        jsonObj["newPassword"] = newPassword.toString();
        jsonObj["name"] = name.toString();
        QJsonArray jsonArray;
        jsonArray.append(jsonObj);
        QJsonObject toSend;
        toSend["editUser"] = jsonArray;
        m_remote->sendToServer(jsonToVariant(toSend));
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

void User::setThisDeviceModel(QString deviceModel)
{
    m_deviceModel = deviceModel;
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

bool User::darkTheme()
{
    QSettings setting;
    if(setting.contains("isDarkTheme")){
        return setting.value("isDarkTheme").toBool();
    }
    else{
        setting.setValue("isDarkTheme",false);
        return setting.value("isDarkTheme").toBool();
    }
}

void User::setDarkTheme(bool value)
{
    QSettings setting;
    setting.setValue("isDarkTheme",value);
    emit darkThemeSig();
}

void User::logOut()
{
    QSettings setting;
    setting.remove("email");
    //setting.remove("serverDomain");
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
    m_remote->sendToServer(jsonToVariant(toSend));
}

QVariant User::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject User::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}

void User::initActivity()
{
    m_remote->initActivity();
}

void User::ping(QVariant payload)
{
    m_remote->ping(payload.toString().toUtf8());
}

void User::onPong(int elapsedTime, QByteArray payload)
{
    QString stringPayload = payload;
    setPong(elapsedTime);
    setPongPayload(stringPayload);
}

void User::reconnect()
{
    m_remote->reconnect();
}

bool User::getIsFullScreen()
{
    QSettings setting;
    if(setting.contains("isFullScreen")){
        m_isFullScreen = setting.value("isFullScreen").toBool();
    }
    else {
        setting.setValue("isFullScreen",false);
        m_isFullScreen = false;
    }
    return m_isFullScreen;
}

void User::setIsFullScreen(bool value)
{
    QSettings setting;
    setting.setValue("isFullScreen",value);
    m_isFullScreen = value;
    emit setFullScreenSig();
}

QString User::getPongPayload() const
{
    return m_pongPayload;
}

void User::setPongPayload(QString pongPayload)
{
    m_pongPayload = pongPayload;
    emit pongPayloadSig();
}

void User::restartService()
{
//    QAndroidJniObject::callStaticMethod<void>("id/web/witchcraft/house/MyService",
//                                                  "startMyService",
//                                                  "(Landroid/content/Context;)V",
//                                                  QtAndroid::androidActivity().object());
    emit restartServiceSig();
}

int User::getPong() const
{
    return m_pong;
}

void User::setPong(int pong)
{
    m_pong = pong;
    emit pongSig();
}
