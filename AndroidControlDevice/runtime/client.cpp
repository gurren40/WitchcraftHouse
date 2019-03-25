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
    //connect(this,&Client::sendToServer,m_remote,&RemoteReplica::sendToServer); // well, you can do it directly from m_remote :3
    connect(m_remote,&RemoteReplica::setIsOnlineSig,m_user,&User::setIsOnline);
    connect(m_remote,&RemoteReplica::tokenExpiredSig,this,&Client::onTokenExpired);
}

void Client::logOut()
{
    QSettings setting;
    setting.remove("email");
    setting.remove("serverDomain");
    setting.remove("jwt");
    emit m_user->isLoggedInSig();
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
        //m_user->setUserInfo(json);
    }
    if(json.contains("deviceList")){
        m_deviceList->setDeviceList(json);
    }
    if(json.contains("groupList")){
        m_groupList->setGroupList(json);
    }
    if(json.contains("pinList")){
        m_pinList->setPinList(json,false);
    }
    if(json.contains("scheduleList")){
        m_scheduleList->setScheduleList(json);
    }
    if(json.contains("sharedList")){
        m_sharedList->setSharedList(json);
    }
    if(json.contains("sharedPinList")){
        m_sharedPinList->setPinList(json,true);
    }
    if(json.contains("settedPinValue")){
        settedPinValue(json);
    }
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

void Client::setSharedPinList(PinList *sharedPinList)
{
    m_sharedPinList = sharedPinList;
}

void Client::setUser(User *user)
{
    m_user = user;
}

void Client::setControlDeviceList(ControlDeviceList *controlDeviceList)
{
    m_controlDeviceList = controlDeviceList;
}

void Client::setSharedList(SharedList *sharedList)
{
    m_sharedList = sharedList;
}

void Client::setScheduleList(ScheduleList *scheduleList)
{
    m_scheduleList = scheduleList;
}

void Client::setGroupList(GroupList *groupList)
{
    m_groupList = groupList;
}

void Client::setDeviceList(DeviceList *deviceList)
{
    m_deviceList = deviceList;
}

void Client::setPinList(PinList *pinList)
{
    m_pinList = pinList;
}

