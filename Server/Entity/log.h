#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTextStream>
#include <QVector>
#include <QDateTime>

struct log{
    int logID;
    int userID;
    QString userName;
    QString description;
    QDateTime timeStamp;
};

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = nullptr);
    explicit Log(QSqlDatabase *database, QObject *parent = nullptr);

    QVector<log> mLogs;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(int userID, QString description);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int logID, int userID, QString description);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // LOG_H
