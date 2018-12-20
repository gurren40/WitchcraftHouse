#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QUrl>

class backend : public QObject
{
    Q_OBJECT
public:
    explicit backend(QObject *parent = nullptr);

signals:
    void getDeviceValueDammnit();
    void setValueDevice(QString uuid, QString value);
    void setWebSocketCreate(QUrl url);

public slots:

    void initDevicesValue();
    void setValue(QString uuid, QString value);
    void setWebSocket(QString urlString);
};

#endif // BACKEND_H
