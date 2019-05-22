#ifndef LOGLISTVIEW_H
#define LOGLISTVIEW_H

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

class LogListView : public QObject
{
    Q_OBJECT
public:
    explicit LogListView(QObject *parent = nullptr);

    QVector<logItem> items() const;

    void setLogItems(const QVector<logItem> &logItems);
    bool setItemAt(int index, const logItem &item);

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
    QVector<logItem> mItems;
};

#endif // LOGLIST_H
