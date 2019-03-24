#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

class Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isOnline READ getIsOnline WRITE setIsOnline NOTIFY isOnlineChanged)
    Q_PROPERTY(bool isLoggedIn READ getIsLoggedIn NOTIFY isLoggedInChanged)
    Q_PROPERTY(QString userEmail READ getUserEmail WRITE setUserEmail)
    Q_PROPERTY(QString serverDomain READ getServerDomain WRITE setServerDomain)
    Q_PROPERTY(QString token READ getToken)

public:
    explicit Client(QObject *parent = nullptr);
    explicit Client(RemoteReplica *remote, QObject *parent = nullptr);

    RemoteReplica *getRemote() const;
    void setRemote(RemoteReplica *remote);

    //property isOnline
    bool getIsOnline() const;
    void setIsOnline(bool isOnline);
    //property isLoggedIn
    bool getIsLoggedIn();
    //property userEmail
    QString getUserEmail();
    void setUserEmail(QString userEmail);
    //property serverDomain
    QString getServerDomain();
    void setServerDomain(QString serverDomain);
    //property token

signals:
    void sendToServer(QJsonObject json);
    //property isOnline
    void isOnlineChanged();
    //property isLoggedIn
    void isLoggedInChanged();

public slots:
    //client specific slot
    void logOut();
    void onTokenExpired(bool value);

    //misc
    QString getDeviceModel(); //not implemented yet

    //another bussiness from server
    void fromServer(QJsonObject json); //not implemented yet

    //call the lists //all not implemented yet
    void deviceList();
    void groupList();
    void pinList();
    void scheduleList();
    void sharedList();
    void controlDeviceList();

    //TO SET FOR MODEL, CALLED BY THIS CLASS, TRIGERRED BY REMOTE
    //setter list //all not implemented yet
    void setAllData(QJsonObject json);
    void setUserInfo(QJsonObject json);
    void setDeviceList(QJsonObject json);
    void setGroupList(QJsonObject json);
    void setPinList(QJsonObject json);
    void setScheduleList(QJsonObject json);
    void setSharedList(QJsonObject json);
    void setSharedPinList(QJsonObject json);
    void setControlDeviceList(QJsonObject json);

    //setted value //all not implemented yet
    void settedPinValue(QJsonObject json);


    //FUNCTIONS TO CALL FROM QML
    //getter list
    void getAllData(); //not implemented yet
    void getUserInfo();
    void getControlDeviceList();

    //request
    void requestLoginToken(QVariant email, QVariant password);

    //create
    void createNewUser(QVariant email, QVariant name, QVariant password);

    //edit
    void editUser(QVariant email, QVariant name, QVariant password);

    //delete
    void deleteControlDevice(QVariant controlDeviceID);

private:
    RemoteReplica *m_remote;
    bool m_isOnline;
};

#endif // CLIENT_H
