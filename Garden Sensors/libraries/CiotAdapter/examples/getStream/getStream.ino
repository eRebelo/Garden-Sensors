/*
  Ciot Adapter Example
  
  This basic examples demonstrate how to connect 
  in the Ciot Platform in the CC3200 within the energia IDE
*/

#include <SPI.h>
#include <WiFi.h>
#include <CiotAdapter.h>
#include <SimpleTimer.h>
#include <aJSON.h>

#define CIOT_INTERVAL 30000

const String sensorId = "5c:31:3e:05:fe:2a";

CiotAdapter adapter;
SimpleTimer timer;

void setup() {
  // Start serial port
  Serial.begin(9600);
  // start the cc3200 wifi connection and the Smart Config interface
  adapter.initialize();
  timer.setInterval(CIOT_INTERVAL, getDataFromCIOT);
  getDataFromCIOT();
}

void loop() {
  timer.run();
}

void getDataFromCIOT(){  
  String jsonString = adapter.getStream(sensorId);  
  boolean value;
  char jsonChar[jsonString.length() + 1];
  jsonString.toCharArray(jsonChar, jsonString.length() + 1);
  
  aJsonObject* root = aJson.parse(jsonChar);
  if (root != NULL) {
        aJsonObject* query = aJson.getObjectItem(root, "data"); 

        if (query != NULL) {
            aJsonObject* results = aJson.getObjectItem(query, "content"); 
            if (results != NULL) {
                  aJsonObject* title = aJson.getObjectItem(results, "busy"); 
                  if (title != NULL) {
                      value = title->valuebool;
                  }
            }
        }
    }

    if(value)
      Serial.println("Sala indisponível, luz vermelha");
    else
      Serial.println("Sala disponível, luz verde");

  
}