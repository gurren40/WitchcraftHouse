#ifndef PINTYPE_H
#define PINTYPE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>

struct pinType{
    int pinTypeID;
    QString pinTypeName;
};

class PinType : public QObject
{
    Q_OBJECT
public:
    explicit PinType(QObject *parent = nullptr);
    explicit PinType(QSqlDatabase *database, QObject *parent = nullptr);

    QVector<pinType> mPinTypes;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(QString pinTypeName);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int pinTypeID, QString pinTypeName);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // PINTYPE_H
