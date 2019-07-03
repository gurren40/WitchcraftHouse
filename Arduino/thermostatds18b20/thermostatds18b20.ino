#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//inisialisasi wifi
const char* ssid = "BigPond01C5";
const char* password = "9726399032";
const String websocketServerIp = "192.168.0.1000";
const int websocketServerPort = 9000;
const String websocketServerUrl = "/device";

//inisialisasi device
const char* deviceID = "jwt:eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJhZGl0aXlhc2lkYWJ1dGFyQHlhbmRleC5jb20iLCJpc3MiOiJXaXRjaGNyYWZ0SG91c2UiLCJqdGkiOiIzOTJkMTNhMC05NjFhLTQ1ZTgtYWU2Ni0xYTJkN2JlMGI5YzkifQ==.VzmBHy52pEahrZ2v1wwlMxCv0qAV3LlQFkmkR6KyX9s=";
const String ambientTempID = "74346d95-2e75-4e18-ba83-8064a2c86e1b";
const String intendedTempID = "02bf3baa-6cc8-4f1b-8b69-447ae451e430";
const String powerID = "73579023-a032-4142-a4a5-84f7de41f079";
const String stateID = "a7a9501a-ddf1-46dc-a5e1-08ee7c34ae6d";

//actual variable
float ambientTemp = 24;
float intendedTemp = 24;
bool power = false;
int state = 0; //0 = off, 1 = heating, 2 = cooling, 3 = fan only

//inisialisasi pin arduino
#define ONE_WIRE_BUS D5

const int fan = D1; //relay
const int heater = D2; //relay
const int cooler = D3; //relay
const int clk = D7;
const int dio = D6;

//misc
unsigned long startTime;
unsigned long currentTime;
unsigned long elapsedTime;

//inisialisasi objek
//StaticJsonBuffer<1000> jsonBuffer;
StaticJsonDocument<1000> jsonBuffer;
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void turnOn(int relay){
  digitalWrite(relay, 1);
}

void turnOff(int relay){
  digitalWrite(relay, 1);
}

int heating(){
  turnOn(heater);
  turnOff(cooler);
  turnOn(fan);
  power = true;
  return 1;
}

int cooling(){
  turnOff(heater);
  turnOn(cooler);
  turnOn(fan);
  power = true;
  return 2;
}

int fanOnly(){
  turnOff(heater);
  turnOff(cooler);
  turnOn(fan);
  power = true;
  return 3;
}

int allOff(){
  turnOff(heater);
  turnOff(cooler);
  turnOff(fan);
  power = false;
  return 0;
}

void setValue(String uuid, String value){
  if(uuid == intendedTempID){
    if(ambientTemp < value.toFloat()){
      intendedTemp = value.toFloat();
      state = heating();
    }
    else if(ambientTemp > value.toFloat()){
      intendedTemp = value.toFloat();
      state = cooling();
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
    }
    else if(value == "0"){
      state = allOff();
    }
  }
  sendMessage();
}

void sendMessage(){
  String ambientTempStatus;
  String intendedTempStatus;
  String powerStatus;
  String stateStatus;
  String msg;
  String msg1;
  String msg2;
  String msg3;
  String msg4;

  ambientTempStatus = ambientTemp;
  intendedTempStatus = intendedTemp;
  if(power){
    powerStatus = "1";
  }
  else{
    powerStatus = "0";
  }
  if(state == 0){
    stateStatus = "Powered Off";
  }
  else if(state == 1){
    stateStatus = "Heating";
  }
  else if(state == 2){
    stateStatus = "Cooling";
  }
  else if(state == 3){
    stateStatus = "Fan Only";
  }
  else{
    stateStatus = "Off";
  }

  msg1 = "{ \"UUID\" : \""+ambientTempID+"\" , \"value\" : \""+ambientTempStatus+"\"}";
  msg2 = "{ \"UUID\" : \""+intendedTempID+"\" , \"value\" : \""+intendedTempStatus+"\"}";
  msg3 = "{ \"UUID\" : \""+powerID+"\" , \"value\" : \""+powerStatus+"\"}";
  msg4 = "{ \"UUID\" : \""+stateID+"\" , \"value\" : \""+stateStatus+"\"}";
  msg = "{ \"settedPinValue\" : [ "+msg1+","+msg2+","+msg3+","+msg4+" ] }";
  webSocket.sendTXT(msg);
}

void keeper(){
  if(power){
    if(ambientTemp < intendedTemp){
      state = heating();
    }
    else if (ambientTemp > intendedTemp){
      state = cooling();
    }
  }
  else{
    state = allOff();
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type){
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected\n");
      break;
      
    case WStype_CONNECTED:{
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      webSocket.sendTXT("Connected");
    }
      break;
      
    case WStype_TEXT:{
      String payloadString = (const char *)payload;
      Serial.printf("[WSc] get text: %s\n", payload);

      //JsonObject parser = jsonBuffer.parseObject(payload);
      auto error = deserializeJson(jsonBuffer, payload);
      if(error){
        Serial.print("parseObject(");
        Serial.print(payloadString);
        Serial.println(") failed");
        break;
      }

//      if (parser["setPinValue"] == "setValue"){
//        setValue(parser["uuid"],parser["value"]);
//      }
      JsonArray jsonArray = jsonBuffer["setPinValue"];
      for(int m = 0;m<jsonArray.size();m++){
        JsonObject jobject = jsonArray[m];
        setValue(jobject["UUID"],jobject["value"]);
      }
      
      jsonBuffer.clear();
    }
      break;

    case WStype_BIN:{
      Serial.printf("[WSc] get binary length: %u\n", length);
      hexdump(payload, length);

      // send data to server
      // webSocket.sendBIN(payload, length);
      break;
    }
  }
}

void setup() {
  // pinmode
//const int fan = 14; //relay
//const int heater = 15; //relay
//const int cooler = 16; //relay
//const int clk = 12;
//const int dio = 4;
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);
  pinMode(cooler, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(dio, OUTPUT);

  digitalWrite(fan, 1);
  digitalWrite(heater, 1);
  digitalWrite(cooler, 1);
  
  Serial.begin(115200);
  //WiFi.begin(ssid, password);
  WiFiMulti.addAP(ssid, password);
  Serial.println("");

  //menunggu koneksi
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  //inisialisasi websocket

  webSocket.setExtraHeaders(deviceID);
  
  webSocket.begin(websocketServerIp,websocketServerPort,websocketServerUrl);

  webSocket.onEvent(webSocketEvent);

  //webSocket.setAuthorization(user,password);

  webSocket.setReconnectInterval(5000);

  sensors.begin();
  delay(1000);
  sensors.requestTemperatures();
  ambientTemp = sensors.getTempCByIndex(0);
  startTime = millis();
  currentTime = millis();
  elapsedTime = currentTime - startTime;
}

void loop() {
  // put your main code here, to run repeatedly:
  webSocket.loop();
  currentTime = millis();
  elapsedTime = currentTime - startTime;
  if(elapsedTime > 3000){
    sensors.requestTemperatures();
    ambientTemp = sensors.getTempCByIndex(0);
    keeper();
    sendMessage();
    startTime = millis();
  }
}
