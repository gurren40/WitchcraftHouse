#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

struct DeviceItem{
    QString uuid;
    QString type;
    QString group;
    QString ownerEmail;
    QString value;
    QString name;
};

class DeviceModel : public QObject
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = nullptr);
    //explicit DeviceModel(QSqlDatabase *database, QObject *parent = nullptr);
    void setDatabase(QSqlDatabase *database);


signals:

public slots:
    //setter
    //bool setDeviceType(QString uuid, QString type);
    //bool setDeviceGroup(QString uuid, QString group);
    //bool setDeviceOwnerEmail(QString uuid, QString ownerEmail);
    bool setDeviceValue(QString uuid, QString value);

    //getter
    //QString getDeviceType(QString uuid);
    //QString getDeviceGroup(QString uuid);
    //QString getDeviceOwnerEmail(QString uuid);
    //QString getDeviceValue(QString uuid);

    //custom method
    //QJsonObject getDeviceInfo(QString uuid);
    QJsonObject getOwnerDevicesList(QString ownerEmail);

private:
    QSqlDatabase db;
    //static QString table = "device";
};

#endif // DEVICEMODEL_H
