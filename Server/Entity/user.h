#ifndef USER_H
#define USER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextStream>
#include <QVector>

struct user{
    int userID;
    QString email;
    QString password;
    QString name;
};

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

    QVector<user> mUsers;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(QString email, QString password, QString name);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int userID, QString email, QString password, QString name);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // USER_H
