#ifndef LOGSTRUCTS_H
#define LOGSTRUCTS_H
#include <QString>
#include <QDateTime>
#include <QUuid>
struct logItem
{
    int logID;
    int userID;
    QString userName;
    QString description;
    QDateTime timeStamp;
};

struct pinLogItem{
    int pinLogID;
    int userID;
    QString userName;
    int pinID;
    QString pinName;
    QUuid pinUUID;
    int pinTypeID;
    QString pinTypeName;
    QString value;
    QString description;
    QDateTime timeStamp;
};

#endif // LOGSTRUCTS_H
