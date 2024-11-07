/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-client-server-wi-fi/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

//remote pins
int fw = 34;
int back = 35;
int left = 25;
int right = 33;

// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
char move = 'g';

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readMove() {
  return String(move);
  //return String(1.8 * bme.readTemperature() + 32);
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readMove().c_str());
  });

  bool status;
//cool code
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  // status = bme.begin(0x76);  
  // if (!status) {
  //   Serial.println("Could not find a valid BME280 sensor, check wiring!");
  //   while (1);
  // }
  
  // Start server
  server.begin();

  //setup remote pins
  pinMode(fw, INPUT);
  pinMode(back, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
}
 
void loop(){

  //remote control logic
  if (digitalRead(fw) == HIGH) {
    move = 'f';
  }
  else if (digitalRead(right) == HIGH) {
    move = 'r';
  }
  else if (digitalRead(left) == HIGH) {
    move = 'l';
  }
  else if (digitalRead(back) == HIGH) {
    move = 'b';
  }
  else {
    move = 's';
  }

  delayMicroseconds(1000000);
  Serial.println("g");
}
