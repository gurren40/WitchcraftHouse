#ifndef THERMOSTAT_H
#define THERMOSTAT_H

#include <QObject>
#include <QWebSocket>
#include <QTimer>
#include <QSettings>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class Thermostat : public QObject
{
    Q_OBJECT
public:
    explicit Thermostat(QObject *parent = nullptr);

signals:
    void sendJson(QJsonObject json);

public:
    float readTemp();
    float readHumid();
    int heating();
    int cooling();
    int fanOnly();
    int allOff();
    void turnOff(int relay);
    void turnOn(int relay);
    void setPinState();
    void setUuids();

public slots:
    void loop();
    void jsonReceived(QJsonObject json);
    void sendAllValue();


private:
    //common
    QTimer m_timer;
    //pins
    int m_fanPin;
    int m_heaterPin;
    int m_coolerPin;
    int m_dhtPin;
    //values
    float ambientTemp;
    float intendedTemp;
    bool power;
    int state;
    //uuids
    QString ambientTempID;
    QString intendedTempID;
    QString powerID;
    QString stateID;
};

#endif // THERMOSTAT_H
