/*
  Ciot Adapter Example
  
  This basic examples demonstrate how to connect 
  in the Ciot Platform in the CC3200 within the energia IDE
*/

#include <SPI.h>
#include <WiFi.h>
#include <CiotAdapter.h>
#include <SimpleTimer.h>

#define CIOT_INTERVAL 30000
// Specify the number of rows in your array, in this case 3
const int numElements=3;

CiotAdapter adapter;
SimpleTimer timer;

void setup() {
  // Start serial port
  Serial.begin(9600);
  // start the cc3200 wifi connection and the Smart Config interface
  adapter.initialize();
  
  timer.setInterval(CIOT_INTERVAL, sendSensorDataToCIOT);

}

void loop() {
  timer.run();
}

void sendSensorDataToCIOT(){  
 // Define the values of the array to be sent
  String array[numElements][2] =
    {
      {"Name", "Marcelo"},
      {"Age", "26"},
      {"Gender", "Male"}
    };

  // Using the instance of the library, call the method send
  Serial.println(adapter.sendStream(array, numElements));
}