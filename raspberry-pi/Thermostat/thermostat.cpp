#include "thermostat.h"
#include <wiringPi.h>

#define MAX_TIMINGS 85
#define DHT_PIN 2

Thermostat::Thermostat(QObject *parent) : QObject(parent)
{
    setPinState();
    setUuids();
    connect(&m_timer,&QTimer::timeout,this,&Thermostat::loop);
    m_timer.setInterval(10000);
    m_timer.setSingleShot(false);
    m_timer.start();
    pinMode( m_fanPin, OUTPUT );
    pinMode( m_heaterPin, OUTPUT );
    pinMode( m_coolerPin, OUTPUT );
    turnOff(m_fanPin);
    turnOff(m_heaterPin);
    turnOff(m_coolerPin);
}

float Thermostat::readTemp()
{
    float temp;
    int data[5] = { 0, 0, 0, 0, 0 };
    //[IMPLEMENT HERE];
    //m_dhtPin
    //temp = 30;
    uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j			= 0, i;
 
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
 
	/* pull pin down for 18 milliseconds */
	pinMode( DHT_PIN, OUTPUT );
	digitalWrite( DHT_PIN, LOW );
	delay( 18 );
 
	/* prepare to read the pin */
	pinMode( DHT_PIN, INPUT );
    
    /* detect change and read data */
	for ( i = 0; i < MAX_TIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHT_PIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHT_PIN );
 
		if ( counter == 255 )
			break;
 
		/* ignore first 3 transitions */
		if ( (i >= 4) && (i % 2 == 0) )
		{
			/* shove each bit into the storage bytes */
			data[j / 8] <<= 1;
			if ( counter > 16 )
				data[j / 8] |= 1;
			j++;
		}
	}
	
		/*
	 * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	 * print it out if data is good
	 */
	if ( (j >= 40) &&
	     (data[4] == ( (data[0] + data[1] + data[2] + data[3]) & 0xFF) ) )
	{
		float h = (float)((data[0] << 8) + data[1]) / 10;
		if ( h > 100 )
		{
			h = data[0];	// for DHT11
		}
		float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
		if ( c > 125 )
		{
			c = data[2];	// for DHT11
		}
		if ( data[2] & 0x80 )
		{
			c = -c;
		}
		float f = c * 1.8f + 32;
		//printf( "Humidity = %.1f %% Temperature = %.1f *C (%.1f *F)\n", h, c, f );
        temp = c;
        QTextStream(stdout) << "\nyes " << c << " \n";
	}else  {
		//printf( "Data not good, skip\n" );
        temp = ambientTemp;
        QTextStream(stdout) << "\nno good " << " \n";
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
    //set pin input/output
    //here
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
