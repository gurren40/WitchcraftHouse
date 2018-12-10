#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "Model/devicemodel.h"

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);
    QJsonObject sendDeviceList(QString idPengguna); //perlu ditambahkan ownernya siapa

signals:

public slots:
    void setDeviceValue(QJsonObject json);
};

#endif // DEVICECONTROLLER_H
