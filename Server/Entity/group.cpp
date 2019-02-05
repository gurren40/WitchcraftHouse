#include "group.h"

Group::Group(QObject *parent) : QObject(parent)
{

}

Group::Group(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void Group::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject Group::create(int userID, int iconID, QString groupName, QString description)
{
    QString textQuery = "INSERT INTO `Groups` (`userID`,`iconID`,`groupName`,`description`) VALUES ('"+QString::number(userID)+"','"+QString::number(iconID)+"','"+groupName+"','"+description+"');";
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

QJsonObject Group::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT Groups.groupID,Groups.userID,User.name,Groups.iconID,Icon.iconName,Groups.groupName,Groups.description FROM ((Groups INNER JOIN User ON Groups.userID = User.userID) LEFT JOIN Icon ON Groups.iconID = Icon.iconID) WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mGroups.clear();
            while (query.next()){
                group groupObject;
                groupObject.groupID = query.value("Groups.groupID").toInt();
                groupObject.userID = query.value("Groups.userID").toInt();
                groupObject.userName = query.value("User.name").toString();
                groupObject.iconID = query.value("Groups.iconID").toInt();
                groupObject.iconName = query.value("Icon.iconName").toString();
                groupObject.groupName = query.value("Groups.groupName").toString();
                groupObject.description = query.value("Groups.description").toString();
                mGroups.append(groupObject);
            }
            mGroups.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Group::update(int groupID, int userID, int iconID, QString groupName, QString description)
{
    QString textQuery = "UPDATE `Groups` SET userID='"+QString::number(userID)+"',iconID='"+QString::number(iconID)+"',groupName='"+groupName+"',description='"+description+"' WHERE groupID='"+QString::number(groupID)+"';";
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

QJsonObject Group::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `Groups` WHERE "+wherequery+";";
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
