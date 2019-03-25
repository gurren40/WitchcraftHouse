#ifndef USER_H
#define USER_H

#include <QObject>
#include <QSettings>
#include <QAndroidJniObject>
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

public:
    explicit User(QObject *parent = nullptr);

    bool isOnline() const;
    bool isTokenExpired() const;
    bool isLoggedIn();
    QString serverDomain();
    QString email();
    QString thisDeviceModel();

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:
    void isOnlineSig(bool isOnline);
    void isTokenExpiredSig(bool isTokenExpired);
    void isLoggedInSig();
    void serverDomainSig(QString serverDomain);
    void emailSig(QString email);

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

private:
    bool m_isOnline;
    bool m_isTokenExpired;
    bool m_isLoggedIn;
//    QString m_serverDomain;
//    QString m_email;
    RemoteReplica *m_remote;
};

#endif // USER_H
