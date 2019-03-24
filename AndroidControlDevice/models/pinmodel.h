#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>

class PinList;

class PinModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PinList *list READ list WRITE setList)

public:
    explicit PinModel(QObject *parent = nullptr);

    enum {
//        DoneRole = Qt::UserRole,
//        DescriptionRole
        //int pinID;
        pinIDRole = Qt::UserRole,
        //QString UUID;
        UUIDRole,
        //int userID;
        userIDRole,
        //QString userName;
        userNameRole,
        //int groupID;
        groupIDRole,
        //QString groupName;
        groupNameRole,
        //int deviceID;
        deviceIDRole,
        //QString deviceName;
        deviceNameRole,
        //int iconID;
        iconIDRole,
        //QString iconName;
        iconNameRole,
        //int pinTypeID;
        pinTypeIDRole,
        //QString pinTypeName;
        pinTypeNameRole,
        //QString pinName;
        pinNameRole,
        //QString value;
        valueRole,
        //QString option;
        optionRole,
        //QString description;
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

    PinList *list() const;
    void setList(PinList *list);

private:
    PinList *mList;
};

#endif // TODOMODEL_H
