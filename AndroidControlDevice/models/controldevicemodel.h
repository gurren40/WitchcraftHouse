#ifndef CONTROLDEVICEMODEL_H
#define CONTROLDEVICEMODEL_H

#include <QAbstractListModel>

class ControlDeviceList;

class ControlDeviceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ControlDeviceList *list READ list WRITE setList)

public:
    explicit ControlDeviceModel(QObject *parent = nullptr);

    enum {
//        DoneRole = Qt::UserRole,
//        DescriptionRole
//        int controlDeviceID;
        controlDeviceIDRole,
//        int userID;
        userIDRole,
//        QString userName;
        userNameRole,
//        QString controlDeviceName;
        controlDeviceNameRole,
//        QString controlDeviceToken;
        controlDeviceTokenRole,
//        bool isControlDeviceOnline;
        isControlDeviceOnlineRole,
//        QDate expireDate;
        expireDateRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ControlDeviceList *list() const;
    void setList(ControlDeviceList *list);

private:
    ControlDeviceList *mList;
};

#endif // CONTROLDEVICEMODEL_H
