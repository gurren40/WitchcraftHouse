#ifndef ICON_H
#define ICON_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>

struct icon{
    int iconID;
    QString iconName;
};

class Icon : public QObject
{
    Q_OBJECT
public:
    explicit Icon(QObject *parent = nullptr);
    explicit Icon(QSqlDatabase *database, QObject *parent = nullptr);

    QVector<icon> mIcons;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(QString iconName);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int iconID, QString iconName);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // ICON_H
