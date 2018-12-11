#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent)
{

}

void DeviceModel::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
}

bool DeviceModel::setDeviceValue(QString uuid, QString value)
{
    if(db.open()){
        bool ok;
        QString theQuery;
        QSqlQuery query(db);
        theQuery = "\
         update device\
         set value = "+value+"\
         where uuid = "+uuid+"\
        ";
        ok = query.exec(theQuery);
        return ok;
    }
    return false;
}

QJsonObject DeviceModel::getOwnerDevicesList(QString ownerEmail)
{
    QJsonObject json;
    QJsonArray objectArray;
    if(db.open()){
        bool ok;
        QString theQuery;
        QSqlQuery query(db);
        theQuery = "\
         Select * from Device \
         where ownerEmail \
         = '"+ ownerEmail +"'\
        ";
        ok = query.exec(theQuery);
        if(ok){
            while(query.next()){
                QJsonObject theObject;
                theObject["uuid"] = query.value("uuid").toString();
                theObject["type"] = query.value("type").toString();
                theObject["group"] = query.value("group").toString();
                theObject["ownerEmail"] = query.value("ownerEmail").toString();
                theObject["value"] = query.value("value").toString();
                theObject["name"] = query.value("name").toString();
                objectArray.append(theObject);
            }
            json["DeviceList"] = objectArray;
            json["function"] = "getDeviceList";
            return json;
        }
        json["message"] = "error gawat 2" + query.lastError().text();
        return json;
    }
    json["message"] = "error gawat 1";
    return json;
}
