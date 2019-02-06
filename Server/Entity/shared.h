#ifndef SHARED_H
#define SHARED_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>
#include <QUuid>

struct shared{
    int sharedID;
    int sharedBy;
    QString sharedByName;
    int sharedTo;
    QString sharedToName;
    bool sharedType;
    int groupID;
    QString groupName;
    int pinID;
    QUuid pinUUID;
    QString pinName;
    QString sharedName;
    QString description;
};

class Shared : public QObject
{
    Q_OBJECT
public:
    explicit Shared(QObject *parent = nullptr);
    explicit Shared(QSqlDatabase *database, QObject *parent = nullptr);

    QVector<shared> mShareds;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(int sharedBy, int sharedTo,  bool sharedType, int groupID, int pinID, QString sharedName, QString description);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int sharedID, int sharedBy, int sharedTo,  bool sharedType, int groupID, int pinID, QString sharedName, QString description);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // SHARED_H
