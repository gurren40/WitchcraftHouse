#ifndef SHAREDMODEL_H
#define SHAREDMODEL_H

#include <QAbstractListModel>

class SharedList;

class SharedModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(SharedList *list READ list WRITE setList)

public:
    explicit SharedModel(QObject *parent = nullptr);

    enum {
//        DoneRole = Qt::UserRole,
//        DescriptionRole
//        int sharedID;
        sharedIDRole,
//        QString sharedTo;
        sharedToRole,
//        QString sharedToName;
        sharedToNameRole,
//        int groupID;
        groupIDRole,
//        QString groupName;
        groupNameRole,
//        QString sharedName;
        sharedNameRole,
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

    SharedList *list() const;
    void setList(SharedList *list);

private:
    SharedList *mList;
};

#endif // SHAREDMODEL_H
