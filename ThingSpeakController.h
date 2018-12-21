#ifndef THINGSPEAKCONTROLLER_H
#define THINGSPEAKCONTROLLER_H

#include <ESP8266WebServer.h>
#include <WiFiClient.h>


#define FIELD_MAX 7

class ThingSpeakController 
{

public:

	ThingSpeakController();
	void Setup(String thingSpeakApiKey);
	void SendMeasurements();

	void Field(int index, String value);


private:
	String _field[FIELD_MAX];
	bool _toSend[FIELD_MAX];

	// replace with your channel’s thingspeak API key,
	String _thingSpeakApiKey;
	char* _thingSpeakServerURL = "api.thingspeak.com";;
	WiFiClient* _thingSpeakClient = new WiFiClient();
	unsigned long _thingSpeakDelay = millis();
};

#endif
