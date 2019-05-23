#ifndef PINLOGVIEWMODEL_H
#define PINLOGVIEWMODEL_H

#include <QAbstractListModel>

class PinLogListView;

class PinLogViewModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PinLogListView *list READ list WRITE setList)

public:
    explicit PinLogViewModel(QObject *parent = nullptr);

    enum {
//        int pinLogID;
        pinLogIDRole,
//        int userID;
        userIDRole,
//        QString userName;
        userNameRole,
//        int pinID;
        pinIDRole,
//        QString pinName;
        pinNameRole,
//        QString pinUUID;
        pinUUIDRole,
//        int pinTypeID;
        pinTypeIDRole,
//        QString pinTypeName;
        pinTypeNameRole,
//        QString value;
        valueRole,
//        QString description;
        descriptionRole,
//        QDateTime timeStamp;
        timeStampRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    PinLogListView *list() const;
    void setList(PinLogListView *list);

private:
    PinLogListView *mList;
};

#endif // PINLOGVIEWMODEL_H
