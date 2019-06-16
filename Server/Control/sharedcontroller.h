#ifndef SHAREDCONTROLLER_H
#define SHAREDCONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>

#include "Entity/shared.h"
#include "Entity/user.h"
#include "Entity/pin.h"
#include "Entity/log.h"

class SharedController : public QObject
{
    Q_OBJECT
public:
    explicit SharedController(QObject *parent = nullptr);
    explicit SharedController(QSqlDatabase *database, QObject *parent = nullptr);

signals:

public slots:
    void setDatabase(QSqlDatabase *database);

    //from signal
    //void deletedPin(QUuid pinUUID,int userID);
    //void deletedGroup(int groupID, int userID);

    //primary function
    QJsonObject createNewShared(QJsonObject json, int userID);
    QJsonObject editShared(QJsonObject json, int userID);
    QJsonObject deleteShared(QJsonObject json, int userID);
    //getSharedList is towarded for sharer, while getSharedPinList is for whom shared to
    QJsonObject getSharedList(int userID);
    QJsonObject getSharedPinList(int userID);

    //misc
    int getSharedToID(QString email);
    QString getSharedToEmail(int sharedToID);

    //delete! delete!
    void deletedGroup(int groupID, int userID);

private:
    QSqlDatabase db;
};

#endif // SHAREDCONTROLLER_H
