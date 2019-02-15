#include "simplesmtp.h"

SimpleSMTP::SimpleSMTP(QString senderEmail, QString senderPassword, QString senderServer, QObject *parent) : QObject (parent)
{
    this->senderEmail = senderEmail;
    this->senderPassword = senderPassword;
    this->senderServer = senderServer;
}

void SimpleSMTP::sendMail(QString sendTo, QString subject, QString body)
{
    Smtp* smtp = new Smtp(senderEmail,senderPassword,senderServer);
    smtp->sendMail(senderEmail,sendTo,subject,body);
}

void SimpleSMTP::mailSent(QString status)
{
    if(status == "Failed to send message"){
        QTextStream(stdout) << status;
        emit mailFail(status);
    }
}
