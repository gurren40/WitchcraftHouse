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

public slots:

    void initDevicesValue();
};

#endif // BACKEND_H
