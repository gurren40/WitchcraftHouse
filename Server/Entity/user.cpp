#include "user.h"

User::User(QObject *parent) : QObject(parent)
{

}

User::User(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

QJsonObject User::createUser(QJsonObject json)
{
    QString query;
    QJsonArray users;
    QJsonObject user;
    QSqlQuery queryObject(db);
    int i;
    bool ok;
    QJsonObject response;
    if(db.open()){
        query = "INSERT INTO `User` (`email`,`password`,`name`) VALUES";
        users = json["CreateNewUser"].toArray();

        for (i=1;i<=users.size();i++) {
            user = users[i].toObject();
            query = query + " (`"+user["email"].toString()+"`,`"+user["password"].toString()+"`,`"+user["name"].toString()+"`)";
            if(i == users.size()){
                query = query + ";";
            } else {
                query = query + ",";
            }
        }
        ok = queryObject.exec(query);
        if(ok) response["error"] = "0";
        else response["error"] = "1";
    }
    else response["error"] = "1";
    return response;
}
