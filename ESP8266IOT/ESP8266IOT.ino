
#include <ESP8266WiFi.h>

#define ledPin 16
#define fumeSensor 5
#define buzzer 4
#define analogInput 0

//how many clients should be able to telnet to this ESP8266
const int port = 23;
const int MAX_SRV_CLIENTS = 1;
String ssid = "UHWireless";
String password = "";

bool found = false;
bool initilize = false;



WiFiServer server(port);
WiFiClient serverClients[MAX_SRV_CLIENTS];

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); 
  
}

void loop() {
  if(!found){
    if(Serial.available()){
      if(Serial.readStringUntil('e') == "ESP8266"){
        Serial.print("YES");
        found = true;
        digitalWrite(ledPin,HIGH);
        delay(1000);
        digitalWrite(ledPin,LOW);
        Serial.print("YES");
      }       
    }
  }else if(!initilize){
    if(Serial.available()){
       ssid = Serial.readStringUntil('e');
           
    }
  }
}

