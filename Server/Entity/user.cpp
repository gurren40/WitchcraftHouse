#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

User::User(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void User::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject User::create(QString email, QString password, QString name)
{
    QString textQuery = "INSERT INTO `User` (`email`,`password`,`name`) VALUES ('"+email+"','"+password+"','"+name+"');";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject User::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT * FROM User WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mUsers.clear();
            while (query.next()){
                user userObject;
                userObject.userID = query.value("userID").toInt();
                userObject.email = query.value("email").toString();
                userObject.password = query.value("password").toString();
                userObject.name = query.value("name").toString();
                mUsers.append(userObject);
            }
            mUsers.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject User::update(int userID, QString email, QString password, QString name)
{
    QString textQuery = "UPDATE `User` SET email='"+email+"',password='"+password+"',name='"+name+"' WHERE userID='"+QString::number(userID)+"';";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject User::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `User` WHERE "+wherequery+";";
    QSqlQuery query;
    QJsonObject response;
    bool ok;

    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok) response["error"] = "0";
        else {
            QTextStream(stdout) << "Error Query : " << query.lastError().text() << "\n";
            response["error"] = query.lastError().text();
        }
    }
    else response["error"] = db.lastError().text();
    return response;
}
