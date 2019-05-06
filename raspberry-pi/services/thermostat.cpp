#include "thermostat.h"
#include <wiringPi.h>

Thermostat::Thermostat(QObject *parent) : QObject(parent)
{
    setPinState();
    setUuids();
    connect(&m_timer,&QTimer::timeout,this,&Thermostat::loop);
    connect(&m_buttontimer,&QTimer::timeout,this,&Thermostat::buttonValidator);
    buttonIndicator = false;
    m_timer.setInterval(10000);
    m_timer.setSingleShot(false);
    m_timer.start();
    m_buttontimer.setInterval(10);
    m_buttontimer.setSingleShot(false);
    m_buttontimer.start();
    turnOff(m_fanPin);
    turnOff(m_heaterPin);
    turnOff(m_coolerPin);
}

void Thermostat::buttonValidator()
{
    uint8_t state = digitalRead( 3 );
    if(!buttonIndicator && (state == HIGH)){
        buttonIndicator = true;
    }
    else if(buttonIndicator && (state == LOW)){
        buttonIndicator = false;
        if(power){
            power = false;
        }
        else{
            power = true;
        }
        loop();
    }
}

float Thermostat::readTemp()
{
    float temp;
    //[IMPLEMENT HERE]
    QString directory = "/sys/bus/w1/devices/28-"+m_tempid.toUtf8();
    QDir fileDir(directory);
    QFile loadFile(fileDir.path()+"/w1_slave");
    if(!loadFile.open(QIODevice::ReadOnly)){
        QTextStream(stdout) << "Couldn't open file\n";
    }
    QString data(loadFile.readAll());
    if(data.contains("YES")){
        QTextStream(stdout) << "YES!\n";
        temp = QString(data.section("=",2,3)).toFloat() / 1000;
        QTextStream(stdout) << "temp is : " << temp <<"\n";
    }
    else {
        QTextStream(stdout) << "NO :'(!\n";
        temp = ambientTemp;
    }
    //[IMPLEMENT HERE]
    return temp;
}

float Thermostat::readHumid()
{
    float humid;
    //[IMPLEMENT HERE]
    humid = 30;
    //[IMPLEMENT HERE]
    return humid;
}

int Thermostat::heating()
{
    turnOn(m_heaterPin);
    turnOn(m_fanPin);
    turnOff(m_coolerPin);
    return 1;
}

int Thermostat::cooling()
{
    turnOff(m_heaterPin);
    turnOn(m_fanPin);
    turnOn(m_coolerPin);
    return 2;
}

int Thermostat::fanOnly()
{
    turnOff(m_heaterPin);
    turnOn(m_fanPin);
    turnOff(m_coolerPin);
    return 3;
}

int Thermostat::allOff()
{
    turnOff(m_heaterPin);
    turnOff(m_fanPin);
    turnOff(m_coolerPin);
    return 0;
}

void Thermostat::turnOff(int relay)
{
    //[IMPLEMENT HERE]
    digitalWrite( relay, HIGH );
    //[IMPLEMENT HERE]
    QTextStream(stdout) << "relay " << relay << " is turned off\n";
}

void Thermostat::turnOn(int relay)
{
    //[IMPLEMENT HERE]
    digitalWrite( relay, LOW );
    //[IMPLEMENT HERE]
    QTextStream(stdout) << "relay " << relay << " is turned on\n";
}

void Thermostat::setPinState()
{
    QSettings setting;
    //init fanPin
    if(setting.contains("pins/fan")){
        m_fanPin = setting.value("pins/fan").toInt();
    }
    else {
        m_fanPin = 0;
        setting.setValue("pins/fan",m_fanPin);
    }
    //init heaterPin
    if(setting.contains("pins/heater")){
        m_heaterPin = setting.value("pins/heater").toInt();
    }
    else {
        m_heaterPin = 0;
        setting.setValue("pins/heater",m_heaterPin);
    }
    if(setting.contains("pins/cooler")){
        m_coolerPin = setting.value("pins/cooler").toInt();
    }
    else {
        m_coolerPin = 0;
        setting.setValue("pins/cooler",m_coolerPin);
    }
    if(setting.contains("pins/dhtpin")){
        m_dhtPin = setting.value("pins/dhtpin").toInt();
    }
    else {
        m_dhtPin = 0;
        setting.setValue("pins/dhtpin",m_dhtPin);
    }
    //temperature id
    if(setting.contains("tempid")){
        m_tempid = setting.value("tempid").toString();
    }
    else {
        m_tempid = "02089246f320";
        setting.setValue("tempid",m_tempid);
    }
    //set pin input/output
    //here
    pinMode( m_fanPin, OUTPUT );
    pinMode( m_heaterPin, OUTPUT );
    pinMode( m_coolerPin, OUTPUT );
}

void Thermostat::setUuids()
{
    QSettings setting;
    if(setting.contains("uuids/ambientTempID")){
        ambientTempID = setting.value("uuids/ambientTempID").toString();
    }
    else {
        ambientTempID = "uuid";
        setting.setValue("uuids/ambientTempID",ambientTempID);
    }
    if(setting.contains("uuids/intendedTempID")){
        intendedTempID = setting.value("uuids/intendedTempID").toString();
    }
    else {
        intendedTempID = "uuid";
        setting.setValue("uuids/intendedTempID",intendedTempID);
    }
    if(setting.contains("uuids/powerID")){
        powerID = setting.value("uuids/powerID").toString();
    }
    else {
        powerID = "uuid";
        setting.setValue("uuids/powerID",powerID);
    }
    if(setting.contains("uuids/stateID")){
        stateID = setting.value("uuids/stateID").toString();
    }
    else {
        stateID = "uuid";
        setting.setValue("uuids/stateID",stateID);
    }
    ambientTemp = 24;
    intendedTemp = 24;
    power = false;
    state = 0;
}

void Thermostat::loop()
{
    ambientTemp =  readTemp();
    if(power){
        if(intendedTemp > ambientTemp){
            state = heating();
        }
        else {
            state = cooling();
        }
    }
    else{
        state = allOff();
    }
    sendAllValue();
}

void Thermostat::jsonReceived(QJsonObject json)
{
    QJsonArray jsonArray;
    if(json.contains("setPinValue")){
        ambientTemp = readTemp();
        jsonArray = json["setPinValue"].toArray();
        for (int i = 0;i<jsonArray.size();i++) {
            QJsonObject jsonObj = jsonArray.at(i).toObject();
            QString uuid = jsonObj["UUID"].toString();
            QString value = jsonObj["value"].toString();
            if(uuid == intendedTempID){
                if(ambientTemp < value.toFloat()){
                    intendedTemp = value.toFloat();
                    if(power){
                        state = heating();
                    }
                }
                else if(ambientTemp > value.toFloat()){
                    intendedTemp = value.toFloat();
                    if(power){
                        state = cooling();
                    }
                }
                else{
                    intendedTemp = value.toFloat();
                }
            }
            if(uuid == powerID){
                if(value == "1"){
                    if(ambientTemp < intendedTemp){
                        state = heating();
                    }
                    else{
                        state = cooling();
                    }
                    power = true;
                }
                else if(value == "0"){
                    state = allOff();
                    power = false;
                }
            }
        }
        sendAllValue();
    }
}

void Thermostat::sendAllValue()
{
    QJsonArray jsonArray;
    QJsonObject jsonAmbient;
    QJsonObject jsonIntended;
    QJsonObject jsonPower;
    QJsonObject jsonStat;
    jsonAmbient["UUID"] = ambientTempID;
    jsonAmbient["value"] = QString::number(ambientTemp);
    jsonArray.append(jsonAmbient);
    jsonIntended["UUID"] = intendedTempID;
    jsonIntended["value"] = QString::number(intendedTemp);
    jsonArray.append(jsonIntended);
    jsonPower["UUID"] = powerID;
    if(power){
        jsonPower["value"] = "1";
    }
    else {
        jsonPower["value"] = "0";
    }
    jsonArray.append(jsonPower);
    jsonStat["UUID"] = stateID;
    if(state == 0){
        jsonStat["value"] = "Off";
    }
    else if(state == 1){
        jsonStat["value"] = "Heating";
    }
    else if(state == 2){
        jsonStat["value"] = "Cooling";
    }
    else if(state == 3){
        jsonStat["value"] = "Fan Only";
    }
    jsonArray.append(jsonStat);
    QJsonObject toSend;
    toSend["settedPinValue"] = jsonArray;
    emit sendJson(toSend);
}
