#include "pinlog.h"

PinLog::PinLog(QObject *parent) : QObject(parent)
{

}

PinLog::PinLog(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void PinLog::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject PinLog::create(int userID, int pinID, QString value, QString description)
{
    QString textQuery = "INSERT INTO `PinLog`(`userID`, `pinID`, `value`, `description`) VALUES ('"+QString::number(userID)+"','"+QString::number(pinID)+"','"+value+"','"+description+"');";
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

QJsonObject PinLog::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT PinLog.pinLogID, PinLog.userID, PinLog.pinID, PinLog.value, PinLog.description, PinLog.timestamp,PinLog.timestamp,UuidFromBin(Pin.UUID),User.name,Pin.pinName,PinType.pinTypeID,PinType.pinTypeName FROM ((PinLog INNER JOIN Pin ON PinLog.pinID = Pin.pinID) LEFT JOIN User ON PinLog.userID = User.userID) LEFT JOIN PinType ON Pin.pinTypeID = PinType.pinTypeID WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mPinLog.clear();
            while (query.next()){
                pinLog pinLogObject;
                pinLogObject.pinLogID = query.value("PinLog.pinLogID").toInt();
                pinLogObject.userID = query.value("PinLog.userID").toInt();
                pinLogObject.userName = query.value("User.name").toString();
                pinLogObject.pinID = query.value("PinLog.pinID").toInt();
                pinLogObject.pinName = query.value("Pin.pinName").toString();
                pinLogObject.pinUUID = query.value("UuidFromBin(Pin.UUID)").toUuid();
                pinLogObject.pinTypeID = query.value("PinType.pinTypeID").toInt();
                pinLogObject.pinTypeName = query.value("PinType.pinTypeName").toString();
                pinLogObject.value = query.value("PinLog.value").toString();
                pinLogObject.description = query.value("PinLog.description").toString();
                pinLogObject.timeStamp = query.value("PinLog.timestamp").toDateTime();
                mPinLog.append(pinLogObject);
            }
            mPinLog.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject PinLog::update(int pinLogID, int userID, int pinID, QString value, QString description)
{
    QString textQuery = "UPDATE `PinLog` SET \
                        userID='"+QString::number(userID)+"',\
                        pinID='"+QString::number(pinID)+"',\
                        value='"+value+"',\
                        description='"+description+"'\
                        WHERE pinLogID='"+QString::number(pinLogID)+"';";

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

QJsonObject PinLog::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `PinLog` WHERE "+wherequery+";";
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
