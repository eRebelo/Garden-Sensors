#include <CiotAdapter.h>

const int analogInPin = A0, numElements = 2;
int sensorValue = 0;
String sensorType = "", sensorTypeOld = ""; /* WEST, MOIST, DRY */

CiotAdapter adapter;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.print("\nMAC Address: ");
  Serial.println(adapter.getMacAddress());
}

void loop() {

  while (adapter.processConfigButton() == LOW) {     
    adapter.processConfigButton(); // inicia processo de configuração do wi-fi, caso necessário
  }
  
  sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);

  if(sensorValue < 400)
    sensorType = "WET";
  else 
    if(sensorValue > 399 && sensorValue < 700)
      sensorType = "MOIST";
    else 
    if(sensorValue > 700)
      sensorType = "DRY";
  
  Serial.println(sensorType);
  delay(3000);

  if (sensorType != sensorTypeOld) {
    sensorTypeOld = sensorType;
    
    /* Enviando dados à plataforma */
    Serial.println("ENVIANDO DADOS PARA A PLATAFORMA IOT... ***");
    String array[numElements][2] =
    {
      { "hygrometer", sensorType },
      { "sensorvalue", String(sensorValue) }
    };
    Serial.println(adapter.sendStream(array, numElements));
  }
}
