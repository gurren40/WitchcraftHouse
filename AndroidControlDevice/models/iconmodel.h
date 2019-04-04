#ifndef ICONMODEL_H
#define ICONMODEL_H

#include <QAbstractListModel>

class IconList;

class IconModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(IconList *list READ list WRITE setList)

public:
    explicit IconModel(QObject *parent = nullptr);

    enum {
        IconIDRole = Qt::UserRole,
        IconNameRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    IconList *list() const;
    void setList(IconList *list);

private:
    IconList *mList;
};

#endif // ICONMODEL_H
