#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

struct GroupItem
{
    //bool done;
    //QString description;
    int groupID;
    int userID;
    QString userName;
    int iconID;
    QString iconName;
    QString groupName;
    QString description;
};

class GroupList : public QObject
{
    Q_OBJECT
public:
    explicit GroupList(QObject *parent = nullptr);

    QVector<GroupItem> items() const;

    bool setItemAt(int index, const GroupItem &item);
    RemoteReplica *getRemote() const;
    void setRemote(RemoteReplica *remote);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setGroupList(QJsonObject json);
    void getGroupList();
    void createNewGroup(QVariant groupName, QVariant iconID, QVariant description);
    void editGroup(QVariant groupID, QVariant groupName, QVariant iconID, QVariant description);
    void deleteGroup(QVariant groupID);
    //QVariant getGroupIconName(QVariant groupName);

    //misc
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);

private:
    QVector<GroupItem> mItems;
    RemoteReplica *m_remote;
};

#endif // GROUPLIST_H
