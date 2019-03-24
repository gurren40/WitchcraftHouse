#ifndef PINLIST_H
#define PINLIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

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

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setPinList(QJsonObject json);

private:
    QVector<PinItem> mItems;
};

#endif // PINLIST_H
