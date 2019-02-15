#ifndef SIMPLESMTP_H
#define SIMPLESMTP_H

#include <QObject>
#include "Library/SimpleSmtp/smtp.h"
#include "Entity/log.h"
#include "Entity/user.h"

class SimpleSMTP : public QObject
{
    Q_OBJECT
public:
    explicit SimpleSMTP(QString senderEmail, QString senderPassword, QString senderServer, QObject *parent = nullptr);

signals:
    void mailFail(QString status);

public slots:
    void sendMail(QString sendTo, QString subject, QString body);
    void mailSent(QString status);


private:
    QString senderEmail;
    QString senderPassword;
    QString senderServer;
};

#endif // SIMPLESMTP_H
