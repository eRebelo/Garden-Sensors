/* HYGROMETER SENSOR AND HUMIDIT AND TEMPERATURE */
#include <SimpleTimer.h>
#include <CiotAdapter.h>
#include "DHT.h"

#define DHTPIN 4 // what pin we're connected to 
#define DIGITAL_SENSOR 5
#define DHTTYPE DHT22 // DHT 22 (AM2302)

#define CIOT_INTERVAL 15000 // 15 seconds

const int analogInPin = A0, numElements = 4;
int sensorValue = 0, enableDeepSleep = 0;
float t, h;
String sensorType = ""; /* WET, MOIST, DRY */


DHT dht(DHTPIN, DHTTYPE);
CiotAdapter adapter;
SimpleTimer timer;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(DIGITAL_SENSOR, OUTPUT);
  pinMode(DHTPIN, OUTPUT);
  Serial.println("\nMAC Address: " + adapter.getMacAddress());
  
  timer.setInterval(CIOT_INTERVAL, sendDataPlatform);
}

void loop() {
  timer.run();

  digitalWrite(DHTPIN, HIGH);
  digitalWrite(DIGITAL_SENSOR, HIGH);
  
  /* 
   * CONFIGURATIONS WIFI 
   */
  while (adapter.processConfigButton() == LOW) {     
    adapter.processConfigButton(); // inicia processo de configuração do wi-fi, caso necessário
  }
  
  /*
   * READING TEMPERATURE AND HUMIDITY
   */
  t = dht.readTemperature();
  h = dht.readHumidity();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
    Serial.println("Reading DHT again");
    delay(1000);
    t = dht.readTemperature();
    h = dht.readHumidity();
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");

  /*
   * HYGROMETER
   */
  sensorValue = analogRead(analogInPin);
  
  if(sensorValue < 400)
    sensorType = "WET";
  else 
    if(sensorValue > 399 && sensorValue < 700)
      sensorType = "MOIST";
    else 
    if(sensorValue > 700)
      sensorType = "DRY";
      
  Serial.print("Hygrometer value: " + String(sensorValue));
  Serial.print("\t");
  Serial.println("Hygrometer status: " + sensorType + "\n");
  
  delay(1000);
}

void sendDataPlatform(){
  /*
   * SEND DATA TO PLATFORM
   */
  Serial.println("Sending data for Platform IOT...");
  String array[numElements][2] =
  {
    { "hygrometer_status", sensorType },
    { "hygrometer_value", String(sensorValue) },
    { "temperature", String(t) },
    { "humidity", String(h) }
  };
  Serial.println("Status send: " + adapter.sendStream(array, numElements));
  sleepMe();
}

void sleepMe() {
  digitalWrite(DHTPIN, LOW);
  digitalWrite(DIGITAL_SENSOR, LOW);
  
  Serial.println("Deep sleep\n");
  //ESP.deepSleep(60000000, RF_DEFAULT); // 1 minute
  /*ESP.deepSleep(1800000000, WAKE_RF_DEFAULT); // 30 minutes*/
  //ESP.deepSleep(15000000, WAKE_RF_DEFAULT); // 15 seconds
}
