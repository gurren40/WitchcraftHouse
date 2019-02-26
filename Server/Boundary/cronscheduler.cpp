#include "cronscheduler.h"

CronScheduler::CronScheduler(QObject *parent) : QObject(parent)
{

}

void CronScheduler::onSignalEmitted()
{
    QCron *theCron = qobject_cast<QCron *>(sender());
    QUuid scheduleUUID = mCronList.key(theCron);
    setPin thePin = mPinList.value(scheduleUUID);
    QJsonObject response;
    QJsonArray jsonArray;
    QJsonObject jsonObject;
    jsonObject["UUID"] = thePin.UUID.toString(QUuid::WithoutBraces);
    jsonObject["value"] = thePin.value;
    jsonArray.append(jsonObject);
    response["setPinValue"] = jsonArray;
    emit setPinValue(response,thePin.userID);
}

void CronScheduler::createNewCron(QUuid scheduleUUID, QString cronSyntax, QUuid UUID, QString value, int userID)
{
    QCron *cron = new QCron(cronSyntax);
    setPin thePin;
    thePin.UUID = UUID;
    thePin.value = value;
    thePin.userID = userID;
    this->mPinList.insert(scheduleUUID,thePin);
    this->mCronList.insert(scheduleUUID,cron);
    connect(cron,SIGNAL(activated()),this,SLOT(onSignalEmitted()));
}

void CronScheduler::editCron(QUuid scheduleUUID, QString cronSyntax, QUuid UUID, QString value, int userID)
{
    deleteCron(scheduleUUID);
    QCron *cron = new QCron(cronSyntax);
    setPin thePin;
    thePin.UUID = UUID;
    thePin.value = value;
    thePin.userID = userID;
    this->mPinList.insert(scheduleUUID,thePin);
    this->mCronList.insert(scheduleUUID,cron);
    connect(cron,SIGNAL(activated()),this,SLOT(onSignalEmitted()));
}

void CronScheduler::deleteCron(QUuid scheduleUUID)
{
    QCron *cron = mCronList.value(scheduleUUID);
    mCronList.remove(scheduleUUID);
    cron->~QCron();
}
