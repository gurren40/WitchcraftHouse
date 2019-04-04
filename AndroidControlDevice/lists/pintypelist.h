#ifndef PINTYPELIST_H
#define PINTYPELIST_H

#include <QObject>
#include <QVector>

struct PinTypeItem
{
    int pinTypeID;
    QString pinTypeName;
};

class PinTypeList : public QObject
{
    Q_OBJECT
public:
    explicit PinTypeList(QObject *parent = nullptr);

    QVector<PinTypeItem> items() const;

    bool setItemAt(int index, const PinTypeItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    //void removeCompletedItems();

private:
    QVector<PinTypeItem> mItems;
};

#endif // PINTYPELIST_H
