#pragma once

#include <QObject>
#include <QtAndroidExtras>
#include <QAndroidJniObject>

class ExternalFunctions : public QObject
{
    Q_OBJECT
public:
    explicit ExternalFunctions(QObject *parent = nullptr);

signals:

public slots:
    void callAndroidService();
    QString getDeviceModel();
    void sendNotification(int id, QString title, QString body);
};

