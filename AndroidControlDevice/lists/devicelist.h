#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

struct DeviceItem
{
    //bool done;
    //QString description;
    int deviceID;
    QString deviceUUID;
    int userID;
    QString userName;
    QString deviceName;
    QString deviceToken;
    bool isDeviceOnline;
    QString description;
};

class DeviceList : public QObject
{
    Q_OBJECT
public:
    explicit DeviceList(QObject *parent = nullptr);

    QVector<DeviceItem> items() const;

    bool setItemAt(int index, const DeviceItem &item);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setDeviceList(QJsonObject json);

private:
    QVector<DeviceItem> mItems;
};

#endif // TODOLIST_H
