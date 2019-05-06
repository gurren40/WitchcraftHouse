#include "webservice.h"

WebService::WebService(QObject *parent) : QObject(parent)
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
        Pin pin = getPinDataAt(i);
        m_pins.append(pin);
    }
    m_networkManager = new QNetworkAccessManager(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(10000);
    m_timer->setSingleShot(false);

    connect(m_timer,&QTimer::timeout,this,&WebService::loop);

    m_timer->start();
}

void WebService::sendJson(QJsonObject json)
{
    QJsonArray jArray= json["setPinValue"].toArray();
    for(int i = 0;i<jArray.size();i++){
        QJsonObject jObj = jArray.at(i).toObject();
        int j = 1;
        bool keeper = false;
        while ((j<=m_totalUuid) || (!keeper)) {
            Pin pin = m_pins.at(i);
            if(jObj["UUID"].toString() == pin.uuid){
                keeper = true;
                QNetworkRequest request(pin.server+"/set");
                QNetworkReply *reply = m_networkManager->post(request,"UUID="+pin.uuid.toUtf8()+"&value="+pin.server.toUtf8());
                connect(reply,&QNetworkReply::finished,this,&WebService::requestFinished);
            }
            j++;
        }
    }
}

void WebService::loop()
{
    for (int i = 0;i<m_totalUuid;i++) {
        Pin pin = m_pins.at(i);
        QNetworkRequest request(pin.server+"/get");
        QNetworkReply *reply = m_networkManager->get(request);
        connect(reply,&QNetworkReply::finished,this,&WebService::requestFinished);
    }
}

void WebService::requestFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    QJsonDocument jdoc = QJsonDocument::fromJson(reply->readAll());
    emit jsonReceived(jdoc.object());
    reply->deleteLater();
}

Pin WebService::getPinDataAt(int i)
{
    QSettings setting;
    QString theID = QString::number(i);
    QString key = "pin-"+theID;
    Pin pin;
    if(setting.contains(key+"/uuid")){
        pin.uuid = setting.value(key+"/uuid").toString();
    }
    else{
        pin.uuid = "empty";
        setting.setValue(key+"/uuid","empty");
    }
    if(setting.contains(key+"/server")){
        pin.server = setting.value(key+"/server").toString();
    }
    else{
        pin.server = "empty";
        setting.setValue(key+"/server","empty");
    }
    return pin;
}
