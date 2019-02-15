#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QCryptographicHash>
#include <QMessageAuthenticationCode>
#include "Library/QJsonWebToken/qjsonwebtoken.h"
#include "Boundary/simplesmtp.h"

//entity
#include "Entity/user.h"
#include "Entity/controlldevice.h"

class UserController : public QObject
{
    Q_OBJECT
public:
    explicit UserController(QObject *parent = nullptr);
    explicit UserController(QSqlDatabase *database, QObject *parent = nullptr);

signals:
    void sendMail(QString sendTo, QString title, QString body);

public slots:
    void setDatabase(QSqlDatabase *database);
    void setSecret(QString secret);
    QJsonObject createUser(QJsonObject json);
    QJsonObject requestLoginToken(QJsonObject json); //masa expirednya pakai currentSecsSinceEpoch()

private:
    QSqlDatabase db;
    QString secret;
    QString alg;
};

#endif // USERCONTROLLER_H
