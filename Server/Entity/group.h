#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>

struct group{
    int groupID;
    int userID;
    QString userName;
    int iconID;
    QString iconName;
    QString groupName;
    QString description;
};

class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(QObject *parent = nullptr);
    explicit Group(QSqlDatabase *database, QObject *parent = nullptr);

    QVector<group> mGroups;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(int userID, int iconID, QString groupName, QString description);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int groupID, int userID, int iconID, QString groupName, QString description);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // GROUP_H
