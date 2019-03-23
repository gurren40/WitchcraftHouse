#ifndef PIN_H
#define PIN_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

class Pin : public QObject
{
    Q_OBJECT
public:
    explicit Pin(QObject *parent = nullptr);

    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

public slots:
    void getPinList();
    void getSharedPinList();
    void createNewPin(QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description);
    void editPin(QVariant pinID, QVariant UUID, QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description);
    void deletePin(QVariant UUID);

private:
    RemoteReplica *m_remote;
};

#endif // PIN_H
