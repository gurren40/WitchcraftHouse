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
    connect(m_remote,&RemoteReplica::setIsOnlineSig,this,&Client::setIsOnline);
    connect(m_remote,&RemoteReplica::tokenExpiredSig,this,&Client::onTokenExpired);
}

void Client::onTokenExpired(bool value)
{
    if(value){
        m_user->logOut();
    }
    m_user->setIsTokenExpired(value);
}

void Client::fromServer(QJsonObject json)
{
//    loginToken will implemented from service(?)
//    if(json.contains("LoginToken")){
//        setLoginToken();
//    }
    if(json.contains("userInfo")){
        m_user->setUserInfo(json);
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
        m_pinList->settedPinValue(json);
        m_sharedPinList->settedPinValue(json);
    }
}

void Client::setIsOnline(bool value)
{
    m_user->setIsOnline(value);
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

