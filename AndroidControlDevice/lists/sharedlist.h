#ifndef SHAREDLIST_H
#define SHAREDLIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

struct SharedItem
{
    //bool done;
    //QString description;
    int sharedID;
    QString sharedTo;
    QString sharedToName;
    bool sharedType;
    int groupID;
    QString groupName;
    QString pinUUID;
    QString pinName;
    QString sharedName;
    QString description;
};

class SharedList : public QObject
{
    Q_OBJECT
public:
    explicit SharedList(QObject *parent = nullptr);

    QVector<SharedItem> items() const;

    bool setItemAt(int index, const SharedItem &item);
    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setSharedList(QJsonObject json);
    void getSharedList();
    void createNewShared(QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
    void editShared(QVariant sharedID, QVariant sharedName, QVariant sharedTo, QVariant sharedType, QVariant groupID, QVariant pinUUID, QVariant description);
    void deleteShared(QVariant sharedID);

private:
    QVector<SharedItem> mItems;
    RemoteReplica *m_remote;
};

#endif // PINLIST_H
