#include "ThingSpeakController.h"


ThingSpeakController::ThingSpeakController()
{
	for (int i = 0; i < FIELD_MAX; i++) 
	{
		_field[i] = "";
		_toSend[i] = false;
	}
}

void ThingSpeakController::Setup(String thingSpeakApiKey)
{
	_thingSpeakApiKey = thingSpeakApiKey;
}

void ThingSpeakController::SendMeasurements()
{
	unsigned long now = millis();
 
	if (abs(now - _thingSpeakDelay) < 20000) 
	{
		return;
	}

	String postStr = _thingSpeakApiKey;
	bool somethingToSend = false;

	for (int i = 0; i < FIELD_MAX; i++) 
	{
		if (_toSend[i])
		{
			postStr += "&field" + String(i + 1) + "=";
			postStr += _field[i];

			somethingToSend = true;
		}
	}

	



	if (!somethingToSend)
		return;

	if (_thingSpeakClient->connect(_thingSpeakServerURL, 80)) // "184.106.153.149" or api.thingspeak.com
	{ 
		_thingSpeakClient->print("POST /update HTTP/1.1\n");
		_thingSpeakClient->print("Host: api.thingspeak.com\n");
		_thingSpeakClient->print("Connection: close\n");
		_thingSpeakClient->print("X-THINGSPEAKAPIKEY: " + _thingSpeakApiKey + "\n");
		_thingSpeakClient->print("Content-Type: application/x-www-form-urlencoded\n");
		_thingSpeakClient->print("Content-Length: ");
		_thingSpeakClient->print(postStr.length());
		_thingSpeakClient->print("\n\n");
		_thingSpeakClient->print(postStr);
		_thingSpeakClient->print("\r\n\r\n");


		Serial.print("Send to Thingspeak: ");
		Serial.print(postStr);
		Serial.print("\n");

		_thingSpeakClient->stop();
	}


	_thingSpeakDelay = now;

	for (int i = 0; i < FIELD_MAX; i++) 
	{
		_toSend[i] = false;
	}

}

void ThingSpeakController::Field(int index, String value)
{
	if (index >= 0 && index < FIELD_MAX) 
	{
		_field[index] = value;
		_toSend[index] = true;
	}
}


