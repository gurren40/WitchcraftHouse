#ifndef USER_H
#define USER_H

#include <QObject>
#include <QSettings>
//#include <QAndroidJniObject>
//#include <QtAndroidExtras>
#include <QSettings>
#include <QJsonObject>
#include <QJsonArray>
#include "rep_remote_replica.h"

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isOnline READ isOnline NOTIFY isOnlineSig)
    Q_PROPERTY(bool isTokenExpired READ isTokenExpired NOTIFY isTokenExpiredSig)
    Q_PROPERTY(bool isLoggedIn READ isLoggedIn NOTIFY isLoggedInSig)
    Q_PROPERTY(QString serverDomain READ serverDomain WRITE setServerDomain NOTIFY serverDomainSig)
    Q_PROPERTY(QString localDomain READ localDomain WRITE setLocalDomain NOTIFY localDomainSig)
    Q_PROPERTY(bool isLocalDomain READ isLocalDomain WRITE setIsLocalDomain NOTIFY isLocalDomainSig)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailSig)
    Q_PROPERTY(QString thisDeviceModel READ thisDeviceModel)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameSig)
    Q_PROPERTY(QString jwt READ getJwt)
    Q_PROPERTY(bool darkTheme READ darkTheme WRITE setDarkTheme NOTIFY darkThemeSig)
    Q_PROPERTY(int pong READ getPong NOTIFY pongSig)
    Q_PROPERTY(QString pongPayload READ getPongPayload NOTIFY pongSig)
    Q_PROPERTY(bool isFullScreen READ getIsFullScreen WRITE setIsFullScreen NOTIFY setFullScreenSig)

public:
    explicit User(QObject *parent = nullptr);

    bool isOnline() const;
    bool isTokenExpired() const;
    bool isLoggedIn();
    bool isLocalDomain();
    QString serverDomain();
    QString localDomain();
    QString email();
    QString thisDeviceModel();
    QString getJwt();

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

    QString getName() const;
    void setName(const QString &name);

    bool darkTheme();
    void setDarkTheme(bool value);

    int getPong() const;
    void setPong(int pong);

    void setPongPayload(QString pongPayload);

    void restartService();

    QString getPongPayload() const;

    bool getIsFullScreen();
    void setIsFullScreen(bool value);

signals:
    void isOnlineSig();
    void isTokenExpiredSig();
    void isLoggedInSig();
    void isLocalDomainSig();
    void serverDomainSig();
    void localDomainSig();
    void emailSig();
    void nameSig();
    void darkThemeSig();
    void pongSig();
    void pongPayloadSig();
    void restartServiceSig();
    void setFullScreenSig();

public slots:
    void setIsOnline(bool isOnline);
    void setIsTokenExpired(bool isTokenExpired);
//    void setIsLoggedIn(bool isLoggedIn);
    void setServerDomain(const QString &serverDomain);
    void setLocalDomain(const QString &localDomain);
    void setIsLocalDomain(bool value);
    void setEmail(const QString &email);
    void getUserInfo();
    void requestLoginToken(QVariant email, QVariant password);
    void createNewUser(QVariant email, QVariant name, QVariant password);
    void editUser(QVariant email, QVariant name, QVariant oldPassword, QVariant newPassword);
    void setUserInfo(QJsonObject json);
    void setThisDeviceModel(QString deviceModel);

    //misc
    void logOut();
    void getAllData();
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);

    //init activity
    void initActivity();

    //ping pong
    void ping(QVariant payload);
    void onPong(int elapsedTime, QByteArray payload);

    //reconnect
    void reconnect();

private:
    bool m_isOnline;
    bool m_isTokenExpired;
    bool m_isLoggedIn;
    RemoteReplica *m_remote;
    QString m_name;
    int m_pong;
    QString m_pongPayload;
    QString m_deviceModel;
    bool m_isFullScreen;
};

#endif // USER_H
