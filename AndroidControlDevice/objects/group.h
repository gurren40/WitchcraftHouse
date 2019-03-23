#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(QObject *parent = nullptr);

    RemoteReplica *getRemote() const;
    void setRemote(RemoteReplica *remote);

signals:

public slots:
    void getGroupList();
    void createNewGroup(QVariant groupName, QVariant iconID, QVariant description);
    void editGroup(QVariant groupID, QVariant groupName, QVariant iconID, QVariant description);
    void deleteGroup(QVariant groupID);

private:
    RemoteReplica *m_remote;
};

#endif // GROUP_H
