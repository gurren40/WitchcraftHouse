#ifndef USER_H
#define USER_H

#include <QObject>
#include <QSettings>
#include <QAndroidJniObject>
#include <QtAndroidExtras>
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
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailSig)
    Q_PROPERTY(QString thisDeviceModel READ thisDeviceModel)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameSig)
    Q_PROPERTY(QString jwt READ getJwt)
    Q_PROPERTY(bool darkTheme READ darkTheme WRITE setDarkTheme NOTIFY darkThemeSig)

public:
    explicit User(QObject *parent = nullptr);

    bool isOnline() const;
    bool isTokenExpired() const;
    bool isLoggedIn();
    QString serverDomain();
    QString email();
    QString thisDeviceModel();
    QString getJwt();

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

    QString getName() const;
    void setName(const QString &name);

    bool darkTheme();
    void setDarkTheme(bool value);

signals:
    void isOnlineSig();
    void isTokenExpiredSig();
    void isLoggedInSig();
    void serverDomainSig();
    void emailSig();
    void nameSig();
    void darkThemeSig();

public slots:
    void setIsOnline(bool isOnline);
    void setIsTokenExpired(bool isTokenExpired);
//    void setIsLoggedIn(bool isLoggedIn);
    void setServerDomain(const QString &serverDomain);
    void setEmail(const QString &email);
    void getUserInfo();
    void requestLoginToken(QVariant email, QVariant password);
    void createNewUser(QVariant email, QVariant name, QVariant password);
    void editUser(QVariant email, QVariant name, QVariant password);
    void setUserInfo(QJsonObject json);

    //misc
    void logOut();
    void getAllData();
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);

private:
    bool m_isOnline;
    bool m_isTokenExpired;
    bool m_isLoggedIn;
//    QString m_serverDomain;
//    QString m_email;
    RemoteReplica *m_remote;
    QString m_name;
};

#endif // USER_H
