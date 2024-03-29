#ifndef PINLIST_H
#define PINLIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include "rep_remote_replica.h"

struct PinItem
{
    //bool done;
    //QString description;
    int pinID;
    QString UUID;
    int userID;
    QString userName;
    int groupID;
    QString groupName;
    int deviceID;
    QString deviceName;
    int iconID;
    QString iconName;
    int pinTypeID;
    QString pinTypeName;
    QString pinName;
    QString value;
    QString option;
    QString description;
};

class PinList : public QObject
{
    Q_OBJECT
public:
    explicit PinList(QObject *parent = nullptr);

    QVector<PinItem> items() const;

    bool setItemAt(int index, const PinItem &item);
    RemoteReplica *remote() const;
    void setRemote(RemoteReplica *remote);

signals:


    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemDataChanged();
    void postItemDataChanged();

    void itemDataChanged(int first, int last);

public slots:
    void setPinList(QJsonObject json, bool isShared);
    void getPinList();
    void getSharedPinList();
    void createNewPin(QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description);
    void editPin(QVariant pinID, QVariant UUID, QVariant pinName, QVariant groupID, QVariant deviceID, QVariant iconID, QVariant pinTypeID, QVariant value, QVariant option, QVariant description);
    void deletePin(QVariant UUID);
    //pin value
    void setPinValue(QVariant UUID, QVariant value);
    void settedPinValue(QJsonObject json);

    //misc
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);
    int getItemIndex(int id);
    QString getItemName(int id);

private:
    QVector<PinItem> mItems;
    RemoteReplica *m_remote;
};

#endif // PINLIST_H
