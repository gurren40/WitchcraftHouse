#pragma once
//linux extrenal functions

#include <QObject>
#include <QFile>
#include <QTextStream>
//#include <libnotifymm.h>


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

