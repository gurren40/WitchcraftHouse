#include "pintype.h"

PinType::PinType(QObject *parent) : QObject(parent)
{

}

PinType::PinType(QSqlDatabase *database, QObject *parent) : QObject(parent)
{
    this->db = *database;
}

void PinType::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject PinType::create(QString pinTypeName)
{
    QString textQuery = "INSERT INTO `PinType` (`pinTypeName`) VALUES ('"+pinTypeName+"');";
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

QJsonObject PinType::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT * FROM `PinType` WHERE "+wherequery+";";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mPinTypes.clear();
            while (query.next()){
                pinType pinTypeObject;
                pinTypeObject.pinTypeID = query.value("pinTypeID").toInt();
                pinTypeObject.pinTypeName = query.value("pinTypeName").toString();
                mPinTypes.append(pinTypeObject);
            }
            mPinTypes.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject PinType::update(int pinTypeID, QString pinTypeName)
{
    QString textQuery = "UPDATE `PinType` SET pinTypeName='"+pinTypeName+"' WHERE pinTypeID='"+QString::number(pinTypeID)+"';";
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

QJsonObject PinType::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `PinType` WHERE "+wherequery+";";
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
