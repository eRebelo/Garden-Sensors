#ifndef SENDCIOT_H_
#define SENDCIOT_H_

#include <Arduino.h>

typedef void (*log_callback)(void);

class CiotAdapter{
	private:
		void connectToWiFi();
		void startApProvisioning();
		void startDebugMode();
		
		void turnOffStatusLed();
		void turnOnStatusLed();
		void blinkStatusLed(int times, int lengthms);
		static int _statusLedPin;
		static int _statusLedState;
		static int _configButtonPin;
		static int _currentButtonState;
		static int _buttonSecondsCount;
		static byte _previousButtonState;
		static unsigned long _buttonFirstTime;
		
	public:
		bool initialize();		
		String sendStream(String array[][2], int elements);
		String sendLog();
		String sendLog(String array[][2], int elements);
		String getStream(String deviceId);
		int processConfigButton();
		String getMacAddress();
		String getIpAddress();
		String getVdd();
		void writeEEPROM(String qsid, String qpass);
		String readSSID();
		String readPASS();
		
		void startSmartConfig();
};

#endif
