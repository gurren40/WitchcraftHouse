#ifndef LOGLIST_H
#define LOGLIST_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>
#include <QDateTime>
#include <QUuid>
#include <QSettings>
#include "rep_remote_replica.h"
#include "logstructs.h"
#include "loglistview.h"
#include "pinloglistview.h"

class LogList : public QObject
{
    Q_OBJECT
public:
    explicit LogList(QObject *parent = nullptr);

    QVector<logItem> items() const;

    bool setItemAt(int index, const logItem &item);

    void setLoglistview(LogListView *loglistview);

    void setRemote(RemoteReplica *remote);

    void setPinloglistview(PinLogListView *pinloglistview);

signals:

public slots:
    //setter to own list
    void setLogList(QJsonObject json);
    void setPinLogList(QJsonObject json);
    //request
    void getLogListData();
    void getPinLogListData();

    //log
    void getTodayLogList();
    void getThisWeekLogList();
    void getThisMonthLogList();
    void getThisYearLogList();
    void getAllLogList();

    //pinlog
    void getTodayPinLogList(QString pinUUID);
    void getThisWeekPinLogList(QString pinUUID);
    void getThisMonthPinLogList(QString pinUUID);
    void getThisYearPinLogList(QString pinUUID);
    void getAllTimePinLogList(QString pinUUID);

    //delete
    void deleteAllLog();
    void deleteActivityLog();
    void deletePinLog();

    //misc
    QVariant jsonToVariant(QJsonObject json);
    QJsonObject variantToJson(QVariant jvar);

private:
    QVector<logItem> m_logItems;
    QMap<QString,QJsonArray> m_pinLogItems;
    LogListView *m_loglistview;
    PinLogListView *m_pinloglistview;
    RemoteReplica *m_remote;
};

#endif // LOGLIST_H
