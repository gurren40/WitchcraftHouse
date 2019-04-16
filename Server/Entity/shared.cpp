#include "shared.h"

Shared::Shared(QObject *parent) : QObject(parent)
{

}

Shared::Shared(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void Shared::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject Shared::create(int sharedBy, int sharedTo, int groupID, QString sharedName, QString description)
{
    QString textQuery = "INSERT INTO `Shared` (`sharedBy`,`sharedTo`,`groupID`,`sharedName`,`description`) VALUES (\
                        '"+QString::number(sharedBy)+"',\
                        '"+QString::number(sharedTo)+"',\
                        '"+QString::number(groupID)+"',\
                        '"+sharedName+"',\
                        '"+description+"');";
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

QJsonObject Shared::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT * FROM \
                         (((Shared s INNER JOIN User s1 ON s.sharedBy = s1.userID) \
                         INNER JOIN User s2 ON s.sharedTo = s2.userID) \
                         LEFT JOIN Groups g ON s.groupID = g.groupID) \
                         WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mShareds.clear();
            while (query.next()){
                shared sharedObject;
                sharedObject.sharedID = query.value("s.sharedID").toInt();
                sharedObject.sharedBy = query.value("s.sharedBy").toInt();
                sharedObject.sharedByName = query.value("s1.name").toString();
                sharedObject.sharedTo = query.value("s.sharedTo").toInt();
                sharedObject.sharedToName = query.value("s2.name").toString();
                sharedObject.groupID = query.value("s.groupID").toInt();
                sharedObject.groupName = query.value("g.groupName").toString();
                sharedObject.sharedName = query.value("s.sharedName").toString();
                sharedObject.description = query.value("s.description").toString();
                mShareds.append(sharedObject);
            }
            mShareds.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Shared::update(int sharedID, int sharedBy, int sharedTo, int groupID, QString sharedName, QString description)
{
    QString textQuery = "UPDATE `Shared` SET \
                        sharedBy='"+QString::number(sharedBy)+"',\
                        sharedTo='"+QString::number(sharedTo)+"',\
                        groupID='"+QString::number(groupID)+"',\
                        sharedName='"+sharedName+"',\
                        description='"+description+"'\
                        WHERE sharedID='"+QString::number(sharedID)+"';";

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

QJsonObject Shared::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `Shared` WHERE "+wherequery+";";
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

