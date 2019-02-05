#include "icon.h"

Icon::Icon(QObject *parent) : QObject(parent)
{
    //ss
}

Icon::Icon(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void Icon::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject Icon::create(QString iconName)
{
    QString textQuery = "INSERT INTO `Icon` (`iconName`) VALUES ('"+iconName+"');";
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

QJsonObject Icon::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT * FROM `Icon` WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mIcons.clear();
            while (query.next()){
                icon iconObject;
                iconObject.iconID = query.value("iconID").toInt();
                iconObject.iconName = query.value("iconName").toString();
                mIcons.append(iconObject);
            }
            mIcons.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Icon::update(int iconID, QString iconName)
{
    QString textQuery = "UPDATE `Icon` SET iconName='"+iconName+"' WHERE iconID='"+QString::number(iconID)+"';";
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

QJsonObject Icon::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `Icon` WHERE "+wherequery+";";
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
