#ifndef ICONLIST_H
#define ICONLIST_H

#include <QObject>
#include <QVector>

struct IconItem
{
    int iconID;
    QString iconName;
};

class IconList : public QObject
{
    Q_OBJECT
public:
    explicit IconList(QObject *parent = nullptr);

    QVector<IconItem> items() const;

    bool setItemAt(int index, const IconItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    //void removeCompletedItems();

private:
    QVector<IconItem> mItems;
};

#endif // ICONLIST_H
