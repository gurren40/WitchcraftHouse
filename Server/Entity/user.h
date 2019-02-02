#ifndef USER_H
#define USER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class User : public QObject
{

    /*
     * Tabel user terdiri dari :
     * 1. userID (int,unique,PrimaryKey,autoIncrement)
     * 2. email (var(100),unique)
     * 3. password (var(100))
     * 4. name (var(100))
     *
     * Method yang akan dibuat hanya terdiri dari CRUD
     */

    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    explicit User(QSqlDatabase *database, QObject *parent = nullptr);

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject createUser(QJsonObject json);
    QJsonObject readUser(QJsonObject json);
    QJsonObject updateUser(QJsonObject json);
    QJsonObject deleteUser(QJsonObject json);

private:
    QSqlDatabase db;
};

#endif // USER_H
