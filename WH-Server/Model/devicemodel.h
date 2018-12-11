#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QJsonObject>
#include <QSqlDatabase>

struct DeviceItem{
    QString uuid;
    QString type;
    QString group;
    QString ownerEmail;
    QString value;
};

class DeviceModel : public QObject
{
    Q_OBJECT
public:
    QList<DeviceItem>
    explicit DeviceModel(QObject *parent = nullptr);
    explicit DeviceModel(QSqlDatabase *database, QObject *parent = nullptr);

signals:

public slots:
    //setter
    bool setType(QString uuid, QString type);
    bool setGroup(QString uuid, QString group);
    bool setOwnerEmail(QString uuid, QString ownerEmail);
    bool setValue(QString uuid, QString value);

    //getter
    QString getType(QString uuid);
    QString getGroup(QString uuid);
    QString getOwnerEmail(QString uuid);
    QString getValue(QString uuid);

    //custom method
    QJsonObject getDeviceInfo(QString uuid);
    QJsonObject getOwnerDevicesList(QString ownerEmail);

private:
    QSqlDatabase db;
};

#endif // DEVICEMODEL_H
