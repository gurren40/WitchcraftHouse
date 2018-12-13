#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>

class backend : public QObject
{
    Q_OBJECT
public:
    explicit backend(QObject *parent = nullptr);

signals:
    void getDeviceValueDammnit();
    void setValueDevice(QString uuid, QString value);

public slots:

    void initDevicesValue();
    void setValue(QString uuid, QString value);
};

#endif // BACKEND_H
