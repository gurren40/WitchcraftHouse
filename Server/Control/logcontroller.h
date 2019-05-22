#ifndef LOGCONTROLLER_H
#define LOGCONTROLLER_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlDatabase>

//entity
#include "Entity/log.h"
#include "Entity/pinlog.h"
#include "Entity/pin.h"

class LogController : public QObject
{
    Q_OBJECT
public:
    explicit LogController(QObject *parent = nullptr);
    explicit LogController(QSqlDatabase *database, QObject *parent = nullptr);

    void setSecret(const QString &value);
    void setDatabase(const QSqlDatabase &value);

signals:

public slots:
    //getter
    QJsonObject getAllLog(int userID);
    QJsonObject getAllPinLog(int userID);
    QJsonObject getAllActivityLog(int userID);
    QJsonObject getPinLog(int userID, int pinID);

    //deleter
    QJsonObject deleteAllLog(int userID);
    QJsonObject deleteAllPinLog(int userID);
    QJsonObject deleteAllActivityLog(int userID);

private:
    QSqlDatabase db;
    QString secret;
};

#endif // LOGCONTROLLER_H
