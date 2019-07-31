#include "loglist.h"

LogList::LogList(QObject *parent) : QObject(parent)
{

}

void LogList::setLogList(QJsonObject json)
{
    QJsonArray jsonArr = json["activityLogList"].toArray();
    m_logItems.clear();
    for (int i = 0;i<jsonArr.size();i++) {
        QJsonObject jsonObject = jsonArr.at(i).toObject();
        logItem lotem;
        lotem.logID = jsonObject["logID"].toInt();
        lotem.userID = jsonObject["userID"].toInt();
        lotem.userName = jsonObject["userName"].toString();
        lotem.description = jsonObject["description"].toString();
        lotem.timeStamp = QDateTime::fromString(jsonObject["timeStamp"].toString());
        m_logItems.append(lotem);
    }
    m_logItems.squeeze();
}

void LogList::setPinLogList(QJsonObject json)
{
    QJsonObject jsonObj = json["pinLogList"].toObject();
    QJsonArray jsonKeys = jsonObj["keys"].toArray();
    m_pinLogItems.clear();
    for (int i = 0;i<jsonKeys.size();i++) {
        QJsonArray jsonArr = jsonObj[jsonKeys.at(i).toString()].toArray();
        m_pinLogItems.insert(jsonKeys.at(i).toString(),jsonArr);
    }
}

void LogList::getLogListData()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getAllActivityLog"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void LogList::getPinLogListData()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["getAllPinLog"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void LogList::getTodayLogList()
{
    QVector<logItem> loglist;
    QDateTime curTime = QDateTime::currentDateTime();
    for (int i = 0;i<m_logItems.size();i++) {
        QDateTime timestamp = m_logItems.at(i).timeStamp;
        if(curTime.date() == timestamp.date()){
            //m_logItems.at(i);
            //viewLogList.append(m_logItems.at(i));
            logItem logItem = m_logItems.at(i);
            loglist.append(logItem);
        }
    }
    m_loglistview->setLogItems(loglist);
}

void LogList::getThisWeekLogList()
{
    QVector<logItem> loglist;
    QDateTime curTime = QDateTime::currentDateTime();
    for (int i = 0;i<m_logItems.size();i++) {
        QDateTime timestamp = m_logItems.at(i).timeStamp;
        if(curTime.date().year() == timestamp.date().year()){
            if(curTime.date().weekNumber() == timestamp.date().weekNumber()){
                //m_logItems.at(i);
                //viewLogList.append(m_logItems.at(i));
                logItem logItem = m_logItems.at(i);
                loglist.append(logItem);
            }
        }
    }
    m_loglistview->setLogItems(loglist);
}

void LogList::getThisMonthLogList()
{
    QVector<logItem> loglist;
    QDateTime curTime = QDateTime::currentDateTime();
    for (int i = 0;i<m_logItems.size();i++) {
        QDateTime timestamp = m_logItems.at(i).timeStamp;
        if(curTime.date().year() == timestamp.date().year()){
            if(curTime.date().month() == timestamp.date().month()){
                //m_logItems.at(i);
                //viewLogList.append(m_logItems.at(i));
                logItem logItem = m_logItems.at(i);
                loglist.append(logItem);
            }
        }
    }
    m_loglistview->setLogItems(loglist);
}

void LogList::getThisYearLogList()
{
    QVector<logItem> loglist;
    QDateTime curTime = QDateTime::currentDateTime();
    for (int i = 0;i<m_logItems.size();i++) {
        QDateTime timestamp = m_logItems.at(i).timeStamp;
        if(curTime.date().year() == timestamp.date().year()){
            //m_logItems.at(i);
            //viewLogList.append(m_logItems.at(i));
            logItem logItem = m_logItems.at(i);
            loglist.append(logItem);
        }
    }
    m_loglistview->setLogItems(loglist);
}

void LogList::getAllLogList()
{
    m_loglistview->setLogItems(m_logItems);
}

void LogList::getTodayPinLogList(QString pinUUID)
{
    QVector<pinLogItem> pinloglist;
    QDateTime today = QDateTime::currentDateTime();
    QJsonArray jsonArr = m_pinLogItems.value(pinUUID);
    for (int i = 0;i<jsonArr.size();i++) {
        QJsonObject logOBj = jsonArr.at(i).toObject();
        QDateTime objTime = QDateTime::fromString(logOBj["timeStamp"].toString());
        if(today.date() == objTime.date()){
            pinLogItem pinlog;
            pinlog.pinLogID = logOBj["pinLogID"].toInt();
            pinlog.userID = logOBj["userID"].toInt();
            pinlog.userName = logOBj["userName"].toString();
            pinlog.pinID = logOBj["pinID"].toInt();
            pinlog.pinName = logOBj["pinName"].toString();
            pinlog.pinUUID = logOBj["pinUUID"].toString();
            pinlog.pinTypeID = logOBj["pinTypeID"].toInt();
            pinlog.pinTypeName = logOBj["pinTypeName"].toString();
            pinlog.value = logOBj["value"].toString();
            pinlog.description = logOBj["description"].toString();
            pinlog.timeStamp = QDateTime::fromString(logOBj["timeStamp"].toString());
            pinloglist.append(pinlog);
        }
    }
    m_pinloglistview->setPinLogItems(pinloglist);
}

void LogList::getThisWeekPinLogList(QString pinUUID)
{
    QVector<pinLogItem> pinloglist;
    QDateTime today = QDateTime::currentDateTime();
    QJsonArray jsonArr = m_pinLogItems.value(pinUUID);
    for (int i = 0;i<jsonArr.size();i++) {
        QJsonObject logOBj = jsonArr.at(i).toObject();
        QDateTime objTime = QDateTime::fromString(logOBj["timeStamp"].toString());
        if(today.date().year() == objTime.date().year()){
            if(today.date().weekNumber() == objTime.date().weekNumber()){
                pinLogItem pinlog;
                pinlog.pinLogID = logOBj["pinLogID"].toInt();
                pinlog.userID = logOBj["userID"].toInt();
                pinlog.userName = logOBj["userName"].toString();
                pinlog.pinID = logOBj["pinID"].toInt();
                pinlog.pinName = logOBj["pinName"].toString();
                pinlog.pinUUID = logOBj["pinUUID"].toString();
                pinlog.pinTypeID = logOBj["pinTypeID"].toInt();
                pinlog.pinTypeName = logOBj["pinTypeName"].toString();
                pinlog.value = logOBj["value"].toString();
                pinlog.description = logOBj["description"].toString();
                pinlog.timeStamp = QDateTime::fromString(logOBj["timeStamp"].toString());
                pinloglist.append(pinlog);
            }
        }
    }
    m_pinloglistview->setPinLogItems(pinloglist);
}

void LogList::getThisMonthPinLogList(QString pinUUID)
{
    QVector<pinLogItem> pinloglist;
    QDateTime today = QDateTime::currentDateTime();
    QJsonArray jsonArr = m_pinLogItems.value(pinUUID);
    for (int i = 0;i<jsonArr.size();i++) {
        QJsonObject logOBj = jsonArr.at(i).toObject();
        QDateTime objTime = QDateTime::fromString(logOBj["timeStamp"].toString());
        if(today.date().year() == objTime.date().year()){
            if(today.date().month() == objTime.date().month()){
                pinLogItem pinlog;
                pinlog.pinLogID = logOBj["pinLogID"].toInt();
                pinlog.userID = logOBj["userID"].toInt();
                pinlog.userName = logOBj["userName"].toString();
                pinlog.pinID = logOBj["pinID"].toInt();
                pinlog.pinName = logOBj["pinName"].toString();
                pinlog.pinUUID = logOBj["pinUUID"].toString();
                pinlog.pinTypeID = logOBj["pinTypeID"].toInt();
                pinlog.pinTypeName = logOBj["pinTypeName"].toString();
                pinlog.value = logOBj["value"].toString();
                pinlog.description = logOBj["description"].toString();
                pinlog.timeStamp = QDateTime::fromString(logOBj["timeStamp"].toString());
                pinloglist.append(pinlog);
            }
        }
    }
    m_pinloglistview->setPinLogItems(pinloglist);
}

void LogList::getThisYearPinLogList(QString pinUUID)
{
    QVector<pinLogItem> pinloglist;
    QDateTime today = QDateTime::currentDateTime();
    QJsonArray jsonArr = m_pinLogItems.value(pinUUID);
    for (int i = 0;i<jsonArr.size();i++) {
        QJsonObject logOBj = jsonArr.at(i).toObject();
        QDateTime objTime = QDateTime::fromString(logOBj["timeStamp"].toString());
        if(today.date().year() == objTime.date().year()){
            pinLogItem pinlog;
            pinlog.pinLogID = logOBj["pinLogID"].toInt();
            pinlog.userID = logOBj["userID"].toInt();
            pinlog.userName = logOBj["userName"].toString();
            pinlog.pinID = logOBj["pinID"].toInt();
            pinlog.pinName = logOBj["pinName"].toString();
            pinlog.pinUUID = logOBj["pinUUID"].toString();
            pinlog.pinTypeID = logOBj["pinTypeID"].toInt();
            pinlog.pinTypeName = logOBj["pinTypeName"].toString();
            pinlog.value = logOBj["value"].toString();
            pinlog.description = logOBj["description"].toString();
            pinlog.timeStamp = QDateTime::fromString(logOBj["timeStamp"].toString());
            pinloglist.append(pinlog);
        }
    }
    m_pinloglistview->setPinLogItems(pinloglist);
}

void LogList::getAllTimePinLogList(QString pinUUID)
{
    QVector<pinLogItem> pinloglist;
    QDateTime today = QDateTime::currentDateTime();
    QJsonArray jsonArr = m_pinLogItems.value(pinUUID);
    for (int i = 0;i<jsonArr.size();i++) {
        QJsonObject logOBj = jsonArr.at(i).toObject();
        pinLogItem pinlog;
        pinlog.pinLogID = logOBj["pinLogID"].toInt();
        pinlog.userID = logOBj["userID"].toInt();
        pinlog.userName = logOBj["userName"].toString();
        pinlog.pinID = logOBj["pinID"].toInt();
        pinlog.pinName = logOBj["pinName"].toString();
        pinlog.pinUUID = logOBj["pinUUID"].toString();
        pinlog.pinTypeID = logOBj["pinTypeID"].toInt();
        pinlog.pinTypeName = logOBj["pinTypeName"].toString();
        pinlog.value = logOBj["value"].toString();
        pinlog.description = logOBj["description"].toString();
        pinlog.timeStamp = QDateTime::fromString(logOBj["timeStamp"].toString());
        pinloglist.append(pinlog);
    }
    m_pinloglistview->setPinLogItems(pinloglist);
}

void LogList::deleteAllLog()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteAllLog"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void LogList::deleteActivityLog()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteAllActivityLog"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void LogList::deletePinLog()
{
    QSettings setting;
    QJsonObject jsonObj;
    jsonObj["email"] = setting.value("email").toString();
    QJsonArray jsonArray;
    jsonArray.append(jsonObj);
    QJsonObject toSend;
    toSend["deleteAllPinLog"] = jsonArray;
    m_remote->sendToServer(jsonToVariant(toSend));
}

void LogList::setLoglistview(LogListView *loglistview)
{
    m_loglistview = loglistview;
}

QVariant LogList::jsonToVariant(QJsonObject json)
{
    QJsonDocument jdoc(json);
    QVariant jvar(jdoc.toJson());
    return jvar;
}

QJsonObject LogList::variantToJson(QVariant jvar)
{
    QJsonDocument jdoc = QJsonDocument::fromJson(jvar.toByteArray());
    QJsonObject json = jdoc.object();
    return json;
}

void LogList::setPinloglistview(PinLogListView *pinloglistview)
{
    m_pinloglistview = pinloglistview;
}

void LogList::setRemote(RemoteReplica *remote)
{
    m_remote = remote;
}
