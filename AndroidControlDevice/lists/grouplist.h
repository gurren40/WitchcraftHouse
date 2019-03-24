#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QObject>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>

struct GroupItem
{
    //bool done;
    //QString description;
    int groupID;
    int userID;
    QString userName;
    int iconID;
    QString iconName;
    QString groupName;
    QString description;
};

class GroupList : public QObject
{
    Q_OBJECT
public:
    explicit GroupList(QObject *parent = nullptr);

    QVector<GroupItem> items() const;

    bool setItemAt(int index, const GroupItem &item);

signals:

    void preItemsResetRemove(int index);
    void postItemResetRemove();
    void preItemsResetAppend(int index);
    void postItemResetAppend();

public slots:
    void setGroupList(QJsonObject json);

private:
    QVector<GroupItem> mItems;
};

#endif // TODOLIST_H
