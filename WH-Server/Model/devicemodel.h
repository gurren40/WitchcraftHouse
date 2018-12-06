#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QObject>

class DeviceModel : public QObject
{
    Q_OBJECT
public:
    explicit DeviceModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DEVICEMODEL_H