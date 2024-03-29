#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>

class DeviceList;

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DeviceList *list READ list WRITE setList)

public:
    explicit DeviceModel(QObject *parent = nullptr);

    enum {
//        DoneRole = Qt::UserRole,
//        DescriptionRole
//        int deviceID;
        deviceIDRole,
//        QString deviceUUID;
        deviceUUIDRole,
//        int userID;
        userIDRole,
//        QString userName;
        userNameRole,
//        QString deviceName;
        deviceNameRole,
//        QString deviceToken;
        deviceTokenRole,
//        bool isDeviceOnline;
        isDeviceOnlineRole,
//        QString description;
        descriptionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    DeviceList *list() const;
    void setList(DeviceList *list);

private:
    DeviceList *mList;
};

#endif // DEVICEMODEL_H
