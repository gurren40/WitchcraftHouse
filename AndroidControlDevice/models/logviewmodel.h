#ifndef LOGVIEWMODEL_H
#define LOGVIEWMODEL_H

#include <QAbstractListModel>

class LogListView;

class LogViewModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(LogListView *list READ list WRITE setList)

public:
    explicit LogViewModel(QObject *parent = nullptr);

    enum {
        logIDrole,
//        int userID;
        userNameRole,
//        QString userName;
        descriptionRole,
//        QString description;
        timeStampRole
//        QDateTime timeStamp;
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    LogListView *list() const;
    void setList(LogListView *list);

private:
    LogListView *mList;
};

#endif // LOGVIEWMODEL_H
