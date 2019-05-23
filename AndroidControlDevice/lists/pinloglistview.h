#ifndef PINLOGLISTVIEW_H
#define PINLOGLISTVIEW_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QDateTime>
#include <QUuid>
#include "logstructs.h"

class PinLogListView : public QObject
{
    Q_OBJECT
public:
    explicit PinLogListView(QObject *parent = nullptr);

    QVector<pinLogItem> items() const;

    void setPinLogItems(const QVector<pinLogItem> &pinLogItems);
    bool setItemAt(int index, const pinLogItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void preItemDataChanged();
    void postItemDataChanged();

    void itemDataChanged(int first, int last);

public slots:
    //setter to own list

private:
    QVector<pinLogItem> mItems;
};

#endif // PINLOGLIST_H
