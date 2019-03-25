#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

//all lists and object
#include "lists/pinlist.h"
#include "lists/devicelist.h"
#include "lists/grouplist.h"
#include "lists/schedulelist.h"
#include "lists/sharedlist.h"
#include "lists/controldevicelist.h"
#include "objects/user.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    explicit Client(RemoteReplica *remote, QObject *parent = nullptr);

    RemoteReplica *getRemote() const;
    void setRemote(RemoteReplica *remote);

    void setPinList(PinList *pinList);

    void setDeviceList(DeviceList *deviceList);

    void setGroupList(GroupList *groupList);

    void setScheduleList(ScheduleList *scheduleList);

    void setSharedList(SharedList *sharedList);

    void setControlDeviceList(ControlDeviceList *controlDeviceList);

    void setUser(User *user);

    void setSharedPinList(PinList *sharedPinList);

signals:

public slots:
    //client specific slot
    void logOut();
    void onTokenExpired(bool value);

    //another bussiness from server
    void fromServer(QJsonObject json); //not implemented yet

    //TO SET FOR MODEL, CALLED BY THIS CLASS, TRIGERRED BY REMOTE
    //setter list
    void setAllData(QJsonObject json);

    //setted value
    void settedPinValue(QJsonObject json);


    //FUNCTIONS TO CALL FROM QML
    //getter list
    void getAllData(); //not implemented yet

    //delete
    void deleteControlDevice(QVariant controlDeviceID);

private:
    RemoteReplica *m_remote;
    PinList *m_pinList;
    DeviceList *m_deviceList;
    GroupList *m_groupList;
    ScheduleList *m_scheduleList;
    SharedList *m_sharedList;
    PinList *m_sharedPinList;
    ControlDeviceList *m_controlDeviceList;
    User *m_user;
};

#endif // CLIENT_H
