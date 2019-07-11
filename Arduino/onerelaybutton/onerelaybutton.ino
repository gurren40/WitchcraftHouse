#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
//#include <DHT.h>

//inisialisasi wifi
const char* ssid = "BigPond01C5";
const char* password = "9726399032";
const String websocketServerIp = "192.168.0.100";
const int websocketServerPort = 9000;
const String websocketServerUrl = "/device";

//inisialisasi device
const char* deviceID = "jwt:eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJhZGl0aXlhc2lkYWJ1dGFyQHlhbmRleC5jb20iLCJpc3MiOiJXaXRjaGNyYWZ0SG91c2UiLCJqdGkiOiI0Yjg3ZTQ2NC02MjY5LTRkNjItYTlmMC1iZmRjYzdmYmY1MGEifQ==.pUK4/FhDfbw1zPKk/1CpJVKrazw/N4rNTucWBixtAOE=";
const String pin1ID = "7497bcb2-26fd-4e4b-9eb5-120122cf9d08";

//pins
const int pin1 = D1; //relay
const int pin2 = D8; //button

//pin status
bool pin1Status = false;
bool pin2Status = false;

//misc
unsigned long startTime;
unsigned long currentTime;
unsigned long elapsedTime;

//inisialisasi objek
//StaticJsonBuffer<1000> jsonBuffer;
StaticJsonDocument<1000> jsonBuffer;
ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;

void turnOn(int relay){
  digitalWrite(relay, 0);
}

void turnOff(int relay){
  digitalWrite(relay, 1);
}

bool setPinValue(int relay, String value){
  bool returnValue = false;
  if(value == "1"){
    turnOn(relay);
    returnValue = true;
  }
  else if(value == "0"){
    turnOff(relay);
  }
  return returnValue;
}

void setValue(String uuid, String value){
  if(uuid == pin1ID){
    pin1Status = setPinValue(pin1,value);
  }
  sendMessage();
}

void sendMessage(){
  String msg;
  String msg1;
  String msgValue1 = "0";

  if(pin1Status){
    msgValue1 = "1";
  }

  msg1 = "{ \"UUID\" : \""+pin1ID+"\" , \"value\" : \""+msgValue1+"\"}";
  msg = "{ \"settedPinValue\" : [ "+msg1+" ] }";
  webSocket.sendTXT(msg);
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
  pinMode(pin1, OUTPUT);
  pinMode(pin2, INPUT);

  digitalWrite(pin1, 1);
  
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
  
  startTime = millis();
  currentTime = 0;
  elapsedTime = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  webSocket.loop();
  currentTime = millis();
  elapsedTime = currentTime - startTime;
  if(elapsedTime > 10000){
    sendMessage();
    startTime = millis();
  }
  if(digitalRead(pin2) == HIGH){
    if(!pin2Status){
      pin2Status = true;
    }
  }
  else{
    if(pin2Status){
      pin2Status = false;
      if(pin1Status){
        pin1Status = setPinValue(pin1, "1");
        sendMessage();
      }
      else{
        pin1Status = setPinValue(pin1, "0");
        sendMessage();
      }
    }
  }
}
