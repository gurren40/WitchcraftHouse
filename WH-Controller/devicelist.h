#ifndef DEVICELIST_H
#define DEVICELIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

struct DeviceItem{
    QString uuid;
    QString type;
    QString group;
    QString ownerEmail;
    QString value;
    QString name;
};

class DeviceList : public QObject
{
    Q_OBJECT
public:
    explicit DeviceList(QObject *parent = nullptr);
    QVector<DeviceItem> items() const;

    bool setItemAt(int index, const DeviceItem &item);
    void requestSetDeviceValue(QString uuid, QString value);
    void initRequestAllDevice();

signals:
    void sendMessageToServer(QJsonObject json);
    void preRewriteAllItem();
    void postRewriteAllItem();
    void preItemAppended();
    void postItemAppended();
    void deviceValueIsSet();

    void preItemRemoved(int index);
    void postItemRemoved();


public slots:
    void rewriteAllItem(QJsonObject json);
    void appendItem(DeviceItem item);
    void removeItem(DeviceItem item);
    void removeItemAtIndex(int index);
    void setDeviceValue(QJsonObject json);

private:
    QVector<DeviceItem> mItems;
};

#endif // DEVICELIST_H
