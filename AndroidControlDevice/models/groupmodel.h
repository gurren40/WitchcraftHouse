#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include <QAbstractListModel>

class GroupList;

class GroupModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(GroupList *list READ list WRITE setList)

public:
    explicit GroupModel(QObject *parent = nullptr);

    enum {
//        DoneRole = Qt::UserRole,
//        DescriptionRole
//        int groupID;
        groupIDRole,
//        int userID;
        userIDRole,
//        QString userName;
        userNameRole,
//        QString groupName;
        groupNameRole,
//        int iconID;
        iconIDRole,
//        QString iconName;
        iconNameRole,
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

    GroupList *list() const;
    void setList(GroupList *list);

private:
    GroupList *mList;
};

#endif // GROUPMODEL_H
