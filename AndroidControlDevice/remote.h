#ifndef REMOTE_H
#define REMOTE_H

#include <QObject>
#include <QDebug>
#include "rep_remote_source.h"

class Remote : public RemoteSource
{
    //Q_OBJECT

public slots:
    void ping(const QString &msg) override;
};

#endif // REMOTE_H
