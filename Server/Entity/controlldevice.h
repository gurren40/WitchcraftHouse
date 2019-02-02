#ifndef CONTROLLDEVICE_H
#define CONTROLLDEVICE_H

#include <QObject>

class ControllDevice : public QObject
{
    Q_OBJECT
public:
    explicit ControllDevice(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CONTROLLDEVICE_H