#ifndef PINTYPEMODEL_H
#define PINTYPEMODEL_H

#include <QAbstractListModel>

class PinTypeList;

class PinTypeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PinTypeList *list READ list WRITE setList)

public:
    explicit PinTypeModel(QObject *parent = nullptr);

    enum {
        PinTypeIDRole = Qt::UserRole,
        PinTypeNameRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    PinTypeList *list() const;
    void setList(PinTypeList *list);

private:
    PinTypeList *mList;
};

#endif // PINTYPEMODEL_H
