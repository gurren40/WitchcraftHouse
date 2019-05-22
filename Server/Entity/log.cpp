#include "log.h"

Log::Log(QObject *parent) : QObject(parent)
{

}

Log::Log(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void Log::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject Log::create(int userID, QString description)
{
    //QString textQuery = "INSERT INTO `Log` (`userID`,`description`,`timeStamp`) VALUES ('"+QString::number(userID)+"','"+description+"','"+QDateTime::currentDateTime().toUTC().toString("yyyy-MM-dd HH:mm:ss")+"');";
    QString textQuery = "INSERT INTO `Log` (`userID`,`description`,`timeStamp`) VALUES ('"+QString::number(userID)+"','"+description+"','"+QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")+"');";
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

QJsonObject Log::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT Log.logID,Log.userID,Log.description,Log.timestamp,User.name FROM Log INNER JOIN User ON Log.userID = User.userID WHERE "+wherequery+" ORDER BY Log.timestamp;";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mLogs.clear();
            while (query.next()){
                log logObject;
                logObject.logID = query.value("Log.logID").toInt();
                logObject.userID = query.value("Log.userID").toInt();
                logObject.userName = query.value("User.name").toString();
                logObject.description = query.value("Log.description").toString();
                logObject.timeStamp = query.value("Log.timeStamp").toDateTime();
                mLogs.append(logObject);
            }
            mLogs.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Log::update(int logID, int userID, QString description)
{
    QString textQuery = "UPDATE `Log` SET \
                        userID='"+QString::number(userID)+"',\
                        description='"+description+"'\
                        WHERE logID='"+QString::number(logID)+"';";

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

QJsonObject Log::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `Log` WHERE "+wherequery+";";
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
