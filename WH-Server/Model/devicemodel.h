#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>

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

signals:

public slots:
    bool setValue(QString value);
};

#endif // DEVICEMODEL_H
