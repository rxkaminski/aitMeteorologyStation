#ifndef WIFISETUP_H
#define WIFISETUP_H

#include <ESP8266WiFi.h>
#include <WiFiClient.h>


class WiFiSetup
{
public:
	void Setup(char* ssid, char* password);
};

#endif

