#include "pin.h"

Pin::Pin(QObject *parent) : QObject(parent)
{

}

Pin::Pin(QSqlDatabase *database, QObject *parent) : QObject (parent)
{
    this->db = *database;
}

void Pin::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

QJsonObject Pin::create(QUuid UUID, int userID, int groupID, int deviceID, int iconID, int pinTypeID, QString pinName, QString value, QString option, QString description)
{
    QString textQuery = "INSERT INTO `Pin` (`UUID`,`userID`,`groupID`,`deviceID`,`iconID`,`pinTypeID`,`pinName`,`value`,`options`,`description`) VALUES \
                        (UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"'),\
                        '"+QString::number(userID)+"',\
                        '"+QString::number(groupID)+"',\
                        '"+QString::number(deviceID)+"',\
                        '"+QString::number(iconID)+"',\
                        '"+QString::number(pinTypeID)+"',\
                        '"+pinName+"',\
                        '"+value+"',\
                        '"+option+"',\
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

QJsonObject Pin::read(QString wherequery)
{
    QJsonObject response;
    QSqlQuery query;
    bool ok;
    QString textQuery = "SELECT *,UuidFromBin(Pin.UUID) FROM (  \
                         ((((Pin INNER JOIN User ON Pin.userID = User.userID) \
                           LEFT JOIN Groups ON Pin.groupID = Groups.groupID) \
                           LEFT JOIN Device ON Pin.deviceID = Device.deviceID) \
                           LEFT JOIN Icon ON Pin.iconID = Icon.iconID) \
                           LEFT JOIN PinType ON Pin.pinTypeID = PinType.pinTypeID \
                         ) WHERE "+wherequery+" \
                         ORDER BY Groups.groupID ASC;";
    if(db.open()){
        QTextStream(stdout) << textQuery << "\n\n";
        ok = query.exec(textQuery);
        if(ok){
            mPins.clear();
            while (query.next()){
                pin pinObject;
                pinObject.pinID = query.value("Pin.pinID").toInt();
                pinObject.UUID = QUuid(query.value("UuidFromBin(Pin.UUID)").toString());
                pinObject.userID = query.value("Pin.userID").toInt();
                pinObject.userName = query.value("User.name").toString();
                pinObject.groupID = query.value("Pin.groupID").toInt();
                pinObject.groupName = query.value("Groups.groupName").toString();
                pinObject.deviceID = query.value("Pin.groupID").toInt();
                pinObject.deviceName = query.value("Device.deviceName").toString();
                pinObject.iconID = query.value("Pin.iconID").toInt();
                pinObject.iconName = query.value("Icon.iconName").toString();
                pinObject.pinTypeID = query.value("Pin.pinTypeID").toInt();
                pinObject.pinTypeName = query.value("PinType.pinTypeName").toString();
                pinObject.pinName = query.value("Pin.pinName").toString();
                pinObject.value = query.value("Pin.value").toString();
                pinObject.option = query.value("Pin.options").toString();
                pinObject.description = query.value("Pin.description").toString();
                mPins.append(pinObject);
            }
            mPins.squeeze();
            response["error"] = "0";
        }
        else response["error"] = query.lastError().text();
    }
    else response["error"] = db.lastError().text();
    return response;
}

QJsonObject Pin::update(int pinID, QUuid UUID, int userID, int groupID, int deviceID, int iconID, int pinTypeID, QString pinName, QString value, QString option, QString description)
{
    QString textQuery = "UPDATE `Pin` SET \
                        UUID=UuidToBin('"+UUID.toString(QUuid::WithoutBraces)+"'),\
                        userID='"+QString::number(userID)+"',\
                        groupID='"+QString::number(groupID)+"',\
                        deviceID='"+QString::number(deviceID)+"',\
                        iconID='"+QString::number(iconID)+"',\
                        pinTypeID='"+QString::number(pinTypeID)+"',\
                        pinName='"+pinName+"',\
                        value='"+value+"',\
                        options='"+option+"',\
                        description='"+description+"'\
                        WHERE pinID='"+QString::number(pinID)+"';";

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

QJsonObject Pin::deletes(QString wherequery)
{
    QString textQuery = "DELETE FROM `Pin` WHERE "+wherequery+";";
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
