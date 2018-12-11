#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent)
{

}

void DeviceModel::setDatabase(QSqlDatabase *database)
{
    this->db = *database;
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
         Select * from device \
         where ownerEmail \
         = '"+ ownerEmail +"'\
        ";
        ok = query.exec();
        if(ok){
            while(query.next()){
                QJsonObject theObject;
                theObject["uuid"] = query.value("uuid").toString();
                theObject["type"] = query.value("type").toString();
                theObject["group"] = query.value("group").toString();
                theObject["ownerEmail"] = query.value("ownerEmail").toString();
                theObject["value"] = query.value("value").toString();
                objectArray.append(theObject);
            }
            json["DeviceList"] = objectArray;
            return json;
        }
        return json;
    }
    return json;
}
