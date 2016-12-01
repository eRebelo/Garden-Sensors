
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


#include "CiotAdapter.h"

int cont = 0;

extern "C" {
#include "user_interface.h"
}


String dataString = "";
WiFiClient client;
char server[] = "api.iot.ciandt.com";

WiFiManager wifiManager;
//int _configButtonPin = 5;
//int _statusLedPin = 13;


int CiotAdapter::_configButtonPin = 5;
int CiotAdapter::_statusLedPin = 13;
int CiotAdapter::_statusLedState = LOW;
int CiotAdapter::_currentButtonState;
int CiotAdapter::_buttonSecondsCount;   // How long the button was held (secs)
byte CiotAdapter::_previousButtonState = LOW;
unsigned long CiotAdapter::_buttonFirstTime;   // how long since the button was first pressed 
log_callback logFunction;

bool CiotAdapter::initialize(){
	
	
//void CiotAdapter::initialize(log_callback f){
	pinMode(_configButtonPin, INPUT_PULLUP);
	pinMode(_statusLedPin, OUTPUT);
	
	Serial.println("Teste LIB222...");
	Serial.println("Starting Library...");
	Serial.print("MAC Address: ");
	Serial.println(getMacAddress());
	
	
	
    if(wifiManager.autoConnect("CiotAdapter", "CiotAdapter"))
	{
		Serial.println("CONECTADO");
		Serial.println("Connected {i}...");
		
	delay(50);
	return true;
	}
	else {
		Serial.println("NÃO CONECTADO");
		return false;
	}
	
	//logFunction = f;
	//Serial.println(sendLog());
}

int CiotAdapter::processConfigButton(){
	_currentButtonState = digitalRead(_configButtonPin);
	//Serial.println(_currentButtonState);
	if (_currentButtonState == LOW && _previousButtonState == HIGH && millis()- _buttonFirstTime > 200){
		_buttonFirstTime = millis();    // if the buttons becomes press remember the time 
		Serial.println("Entered first func...");
	}
	if (_currentButtonState == LOW && ((millis() - _buttonFirstTime) % 1000) < 20 && millis() - _buttonFirstTime > 500){
		pinMode(_statusLedPin, OUTPUT);
			
	
	digitalWrite(_statusLedPin, HIGH);
	delay(100);
	digitalWrite(_statusLedPin, LOW);
		_buttonSecondsCount++;
		Serial.println(_buttonSecondsCount);	
		
		blinkStatusLed(1, 100);
		
		
		
		
	

	}
	if (_currentButtonState == HIGH && _previousButtonState == LOW && _buttonSecondsCount >=6 && _buttonSecondsCount < 7){
		_buttonSecondsCount = 0;
		Serial.println("startApProvisioning();");
		
		
		 startApProvisioning();
	}
	if (_currentButtonState == HIGH && _previousButtonState == LOW && _buttonSecondsCount >=4 && _buttonSecondsCount < 5){
		_buttonSecondsCount = 0;
		startDebugMode();
		
	}
	if (_currentButtonState == HIGH && _previousButtonState == LOW && _buttonSecondsCount >=3 && _buttonSecondsCount < 4){
		_buttonSecondsCount = 0;
		
		Serial.println("startSmartConfig();");
		startSmartConfig();
	}
	if (_currentButtonState == HIGH && _previousButtonState == LOW && _buttonSecondsCount >=2 && _buttonSecondsCount < 3){
		_buttonSecondsCount = 0;
		(*logFunction)();
	}
	if (_currentButtonState == HIGH && _previousButtonState == LOW && _buttonSecondsCount >=1 && _buttonSecondsCount < 2){
		_buttonSecondsCount = 0;
		
		Serial.println("Entered last func...");
		connectToWiFi();
	}
	if (_currentButtonState == HIGH){// && _previousButtonState == LOW) {
		_buttonSecondsCount = 0;
		
		//Serial.println("Entered very last func...");
	}
	_previousButtonState = _currentButtonState;
	
	return _currentButtonState;
}



void CiotAdapter::startSmartConfig(){
	
	WiFi.disconnect();
	
  int cnt = 0;  

  // set for STA mode
  WiFi.mode(WIFI_STA);
  
  // led status at pin16
  pinMode(2,OUTPUT);
  

  // if wifi cannot connect start smartconfig
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
       WiFi.beginSmartConfig();
       while(1){
           delay(500);
           if(WiFi.smartConfigDone()){
             Serial.println("SmartConfig Success");
             break;
           }
       }
    
  }

  Serial.println("");
  Serial.println("");
  
  WiFi.printDiag(Serial);

  // Print the IP address
  Serial.println(WiFi.localIP());  
  //this->_ssid.c_str(), this->_password.
 //writeEEPROM(_ssid, _password);

}




void CiotAdapter::startApProvisioning(){
	
    WiFiManager wifiManager;

		wifiManager.startConfigPortal("CiotAdapter", "CiotAdapter");
    
    Serial.println("Connected...");

  Serial.println(WiFi.localIP());

}



void CiotAdapter::startDebugMode(){
	WiFi.mode(WIFI_OFF);
		delay(300);
	Serial.println("Starting Debug Mode...");
	
	while(1)
	{
		
		if(digitalRead(4))
			digitalWrite(_statusLedPin, HIGH);
		
		else
			digitalWrite(_statusLedPin, LOW);
		
	Serial.print("Sensor status: ");
	Serial.println(digitalRead(4));
	}
}

void CiotAdapter::turnOnStatusLed(){
	_statusLedState = HIGH;
	digitalWrite(_statusLedPin, HIGH);
}

void CiotAdapter::turnOffStatusLed(){
	_statusLedState = LOW;
	digitalWrite(_statusLedPin, LOW);
}

void CiotAdapter::blinkStatusLed(int times, int lengthms){
	for (int x=0; x<times;x++){
		digitalWrite(_statusLedPin, HIGH);
		delay (lengthms);
		digitalWrite(_statusLedPin, LOW);
		delay(lengthms);
  }
}

void CiotAdapter::connectToWiFi(){
	Serial.println("Entered Connect Function");
	
	while ( WiFi.status() == WL_CONNECTED) {
		delay(300);
	}
  Serial.println("Waiting the connection");
  while ( WiFi.status() != WL_CONNECTED) {
	if(processConfigButton() == LOW)
		return;
    Serial.print(".0");
	blinkStatusLed(1, 100);
    delay(300);
  }

  Serial.println("You're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) {
	if(processConfigButton() == LOW)
		return;
    Serial.print(".");
	blinkStatusLed(1, 100);
	
    delay(150);
  }
  Serial.println("IP Address obtained");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  Serial.print("IP Address: ");
  Serial.println(getIpAddress());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  turnOffStatusLed();
 // sendLog();
	
 
}


String CiotAdapter::sendLog(){
  String msg;
  Serial.println("Trying to connect to the server and send information");
  if(WiFi.status() != WL_CONNECTED){
	  msg = "No Internet Connection";
  }else{
	  if (client.connect(server, 80)) {
		Serial.println(F("connected"));
		client.println("POST /v2/log HTTP/1.1");
		String host = "Host:";
		host += server;
		client.println(host);
		client.println("Accept: application/json");
		client.println("User-Agent: Arduino-CIOT");
		client.println("Content-Type: application/json");
		client.println("access_token : ID_TOKEN");
		client.print("id: ");
		client.println(getMacAddress());
		client.print("Content-Length: ");
		int thisLength = dataString.length();
		client.println(thisLength);
		client.println("Connection: close");
		client.println();
		
		client.println(dataString);

		Serial.println("Log sent to the server");

		}
		delay(5);
		long timeoutStart = millis();
		while (!client.available()) {	
			if((millis() - timeoutStart) > 30000){
			  Serial.println("Timeout: waiting the response");
			  client.stop();
			  break;
			}
		}

		while (client.available()) {
			char c = client.read();
			msg += c;
		}

		if (!client.connected()) {
		  client.stop();
		}
  }
  return msg;
}

String CiotAdapter::sendLog(String array[][2], int elements){
  String key;
  String value;
  String msg;
  Serial.println("Trying to connect to the server and send information");
  if(WiFi.status() != WL_CONNECTED){
	  msg = "No Internet Connection";
  }else{
	  if (client.connect(server, 80)) {
		Serial.println(F("connected"));
		dataString = "{\"content\":{";
		for (int i=0; i<elements;i++){
		  key=array[i][0];
		  value=array[i][1];
		  dataString += "\""+key+"\":";
		  dataString += "\""+value+"\"";
		  if (elements>1 && i!=elements-1){
			 dataString += ",";
		  }
		}
			dataString += "}}";

		client.println("POST /v2/log HTTP/1.1");
		String host = "Host:";
		host += server;
		client.println(host);
		client.println("Accept: application/json");
		client.println("User-Agent: Arduino-CIOT");
		client.println("Content-Type: application/json");
		client.println("access_token : ID_TOKEN");
		client.print("id: ");
		client.println(getMacAddress());
		client.print("Content-Length: ");
		int thisLength = dataString.length();
		client.println(thisLength);
		client.println("Connection: close");
		client.println();
		
		client.println(dataString);

		Serial.println("Log sent to the server");

		}
		delay(5);
		long timeoutStart = millis();
		while (!client.available()) {	
			if((millis() - timeoutStart) > 20000){
			  Serial.println("Timeout: waiting the response");
			  client.stop();
			  break;
			}
		}

		while (client.available()) {
			char c = client.read();
			msg += c;
		}

		if (!client.connected()) {
		  client.stop();
		}
  }
  return msg;
}

String CiotAdapter::sendStream(String array[][2], int elements){
  String key;
  String value;
  String msg;
  Serial.println("Trying to connect to the server and send information");
  if(WiFi.status() != WL_CONNECTED){
	  msg = "No Internet Connection";
  }else{
	  if (client.connect(server, 80)) {
		Serial.println(F("connected"));
		dataString = "{\"content\":{";
		for (int i=0; i<elements;i++){
		  key=array[i][0];
		  value=array[i][1];
		  dataString += "\""+key+"\":";
		  dataString += "\""+value+"\"";
		  if (elements>1 && i!=elements-1){
			 dataString += ",";
		  }
		}
		cont++;
		dataString += "}";
		dataString += ",\"uptime\":";
		dataString += String(millis());
		dataString += ",\"battery\":";
		dataString += getVdd();		
		dataString += ",\"firmwareVersion\":\"1.0\"";
		dataString += ",\"ipAddress\":\"";
		dataString += getIpAddress();
		dataString += "\",\"ssid\":\"";
		dataString += WiFi.SSID();	
		dataString += "\"}";
		Serial.print("DataString:\n");
		Serial.println(dataString);

		client.println("POST /v2/data HTTP/1.1");
		String host = "Host:";
		host += server;
		client.println(host);
		client.println("Accept: application/json");
		client.println("User-Agent: Arduino-CIOT");
		client.println("Content-Type: application/json");
		client.println("access_token : ID_TOKEN");
		client.print("id: ");
		client.println(getMacAddress());
		client.print("Content-Length: ");
		int thisLength = dataString.length();
		client.println(thisLength);
		client.println("Connection: close");
		client.println();
		client.println(dataString);
		Serial.println("Data sent to the server");

	   }
	   delay(5);
	   long timeoutStart = millis();
	   
		Serial.print("timeoutStart");
		Serial.println(timeoutStart);
	 	while (!client.available()) {	
			if((millis() - timeoutStart) > 20000){
				Serial.println("Timeout: waiting the response");
				break;
			}
		}
	
		while (client.available()) {
			char c = client.read();
			msg += c;
		}
	
		if (!client.connected()) {
			client.stop();
		}
  return msg;
}
}


String CiotAdapter::getStream(String deviceId){
	String msg;
	Serial.print ("Entered getStream, time: ");	
	Serial.println(millis());
	if(WiFi.status() != WL_CONNECTED){
		msg = "No Internet Connection";
	}else{
		if (client.connect(server, 80)) {
			Serial.println(F("connected"));
			
	Serial.println(millis());
			String request = "GET /v2/data/";
			request += deviceId;
			request += "/last HTTP/1.1";
			client.println(request);
			String host = "Host:";
			host += server;
			client.println(host);
			client.println("User-Agent: Arduino-CIOT");
			client.println("Connection: close");
			client.println();
			delay(5);
			long timeoutStart = millis();
			int jsonFirstChar = 0;
			while(client.connected()){
				while (client.available()) {
					char c = client.read();
					if(c == '{')
						jsonFirstChar = 1;

					if(jsonFirstChar)
						msg += c;
					
					if((millis() - timeoutStart) > 30000){
						break;
						Serial.println("Timeout: waiting the response");
					}
				}
			}
					
			if (!client.connected()) {
				client.stop();
			}	
			Serial.println("Json Received:");
			Serial.println(msg);
			return msg;
		}
	}
	

}

String CiotAdapter::getMacAddress(){
  String macString = "";
  byte mac[6];
  WiFi.macAddress(mac);
  for(int i = 0; i < 6; i++){
    String hex = String(mac[i],HEX);
    if(hex.length() == 1)
      hex = "0" + hex;
    macString += hex ;
    if(i < 5)
      macString += ":";
    }
  return macString;
}

String CiotAdapter::getIpAddress(){
  IPAddress ip  = WiFi.localIP();
  char myIpString[24];
  sprintf(myIpString, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  return myIpString;
}


String CiotAdapter::getVdd(){
	float vcc3 = 0;
	int nowVolt = analogRead(A0);
	
  int nowVolt2 = nowVolt;
  int cont= 0;
  float vcc = (float)nowVolt*4/935;
   Serial.print("Math: ");
  Serial.println(vcc);
  
  Serial.print("Percent: ");
  float vdd2 = (float)(vcc - 3.2)*1000/12;
  Serial.println(vdd2);
  
return (String) vdd2;
}


