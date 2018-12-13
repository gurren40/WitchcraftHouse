#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QUrl>
#include <QUrlQuery>
#include <QList>

#include "Model/devicemodel.h"

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    explicit DeviceController(QSqlDatabase *database, QObject *parent = nullptr);
    void getDeviceList(QUrl url, QJsonObject json); //perlu ditambahkan ownernya siapa
    void setDeviceValue(QUrl url, QJsonObject json);
    void requestSetDeviceValue(QUrl url, QJsonObject json);

signals:
    void sendMessegeToDevice(QString uuid, QUrl url, QJsonObject json);
    void sendMessegeToControllDevice(QUrl url, QJsonObject json);

public slots:
    void fromWebsocket(QUrl url, QJsonObject json);

private:
    QSqlDatabase db;
};

#endif // DEVICECONTROLLER_H
