/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-client-server-wi-fi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverName = "http://192.168.4.1/move";


//pins
int stopPin1 = 13; //right
int stopPin2 = 14; //left
// int left1 = 27;
// int left2 = 32;
// int right1 = 33;
// int right2 = 25;


String move;

unsigned long previousMillis = 0;
const long interval = 1000; 

void setup() {
  Serial.begin(9600);
  Serial.println("NEW CODE SETUP V2 STARTED!");
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  //set up pins
  pinMode(stopPin1, OUTPUT);
  pinMode(stopPin2, OUTPUT);
  // pinMode(left1, OUTPUT);
  // pinMode(left2, OUTPUT);
  // pinMode(right1, OUTPUT);
  // pinMode(right2, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      move = httpGETRequest(serverName);
      Serial.println(move);
      
      if (move.equalsIgnoreCase("s")) {
        digitalWrite(stopPin1, LOW);
        digitalWrite(stopPin2, LOW);
        Serial.println("Stopped");
        digitalWrite(2, LOW);
      }
      else if (move.equalsIgnoreCase("f")) {
        digitalWrite(stopPin1, HIGH);
        digitalWrite(stopPin2, HIGH);
        Serial.println("Forward");
        digitalWrite(2, HIGH);
      }
      else if (move.equalsIgnoreCase("l")){
        digitalWrite(stopPin2, HIGH);
        
        
        Serial.println("Left");
      }
      else if (move.equalsIgnoreCase("r")) {
        digitalWrite(stopPin1, HIGH);
        // digitalWrite(right1, HIGH);
        // digitalWrite(right2, HIGH);
        // digitalWrite(left1, LOW);
        // digitalWrite(left2, LOW);
        Serial.println("Right");
      }
      else if (move.equalsIgnoreCase("b")) {

      }


      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
