#ifndef SHAREDCONTROLLER_H
#define SHAREDCONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>

class SharedController : public QObject
{
    Q_OBJECT
public:
    explicit SharedController(QObject *parent = nullptr);
    explicit SharedController(QSqlDatabase *database, QObject *parent = nullptr);

signals:

public slots:
    void setDatabase(QSqlDatabase *database);

    //primary function
    //QJsonObject createNewShared(QJsonObject json, int userID);
    //QJsonObject editShared(QJsonObject json, int userID);
    //QJsonObject deleteShared(QJsonObject json, int userID);
    //getSharedList is towarded for sharer, while getSharedPinList is for whom shared to
    //QJsonObject getSharedList(int userID);
    //QJsonObject getSharedPinList(int userID, int userID);

private:
    QSqlDatabase db;
};

#endif // SHAREDCONTROLLER_H
