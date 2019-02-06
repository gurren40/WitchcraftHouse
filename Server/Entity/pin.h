#ifndef PIN_H
#define PIN_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QJsonObject>
#include <QVector>
#include <QTextStream>
#include <QUuid>

struct pin{
    int pinID;
    QUuid UUID;
    int userID;
    QString userName;
    int groupID;
    QString groupName;
    int deviceID;
    QString deviceName;
    int iconID;
    QString iconName;
    int pinTypeID;
    QString pinTypeName;
    QString pinName;
    QString value;
    QString option;
    QString description;
};

class Pin : public QObject
{
    Q_OBJECT
public:
    explicit Pin(QObject *parent = nullptr);
    explicit Pin(QSqlDatabase *database, QObject *parent = nullptr);

    QVector<pin> mPins;

signals:

public slots:

    void setDatabase(QSqlDatabase *database);

    QJsonObject create(QUuid UUID, int userID, int groupID, int deviceID, int iconID, int pinTypeID, QString pinName, QString value, QString option, QString description);
    QJsonObject read(QString wherequery = "1");
    QJsonObject update(int pinID, QUuid UUID, int userID, int groupID, int deviceID, int iconID, int pinTypeID, QString pinName, QString value, QString option, QString description);
    QJsonObject deletes(QString wherequery);

private:
    QSqlDatabase db;
};

#endif // PIN_H
