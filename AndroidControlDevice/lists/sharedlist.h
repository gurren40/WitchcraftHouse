#ifndef SHAREDLIST_H
#define SHAREDLIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

struct SharedItem
{
    //bool done;
    //QString description;
    int sharedID;
    QString sharedTo;
    QString sharedToName;
    bool sharedType;
    int groupID;
    QString groupName;
    QString pinUUID;
    QString pinName;
    QString sharedName;
    QString description;
};

class SharedList : public QObject
{
    Q_OBJECT
public:
    explicit SharedList(QObject *parent = nullptr);

    QVector<SharedItem> items() const;

    bool setItemAt(int index, const SharedItem &item);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setSharedList(QJsonObject json);

private:
    QVector<SharedItem> mItems;
};

#endif // PINLIST_H
