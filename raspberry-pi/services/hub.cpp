#include "hub.h"

Hub::Hub(QObject *parent) : QObject(parent)
{
    QSettings setting;
    if(setting.contains("totalUuid")){
        m_totalUuid = setting.value("totalUuid").toInt();
    }
    else {
        m_totalUuid = 4;
        setting.setValue("totalUuid",m_totalUuid);
    }
    for (int i = 1;i<=m_totalUuid;i++) {
        QString theID = QString::number(i);
        QString key = "pin-"+theID;
        if(setting.contains(key+"/uuid")){
            m_uuids.append(setting.value(key+"/uuid").toString());
        }
        else{
            m_uuids.append("empty");
            setting.setValue(key+"/uuid","empty");
        }
    }
}

bool Hub::validateUUID(QString strUuid)
{
    int value = false;
    int i = 0;
    while ((!value) && (i < m_uuids.size())) {
        if(m_uuids.at(i) == strUuid){
            value = true;
        }
        i++;
    }
    return value;
}

void Hub::jsonReceivedFromMain(QJsonObject json)
{
    QJsonArray jArray = json["setPinValue"].toArray();
    for (int i = 0;i<jArray.size();i++) {
        QJsonObject jObj = jArray.at(i).toObject();
        bool isValid = validateUUID(jObj["UUID"].toString());
        if(isValid){
            emit broadcastJson(json);
        }
    }
}

void Hub::jsonReceivedFromClient(QJsonObject json)
{
    QJsonArray jArray = json["settedPinValue"].toArray();
    for (int i = 0;i<jArray.size();i++) {
        QJsonObject jObj = jArray.at(i).toObject();
        bool isValid = validateUUID(jObj["UUID"].toString());
        if(isValid){
            emit sendJsonToMain(json);
        }
    }
}
