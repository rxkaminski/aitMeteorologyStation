#ifndef WWWSITE_H
#define WWWSITE_H

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include "html_index.h" 
#include "Measurement.h"

extern "C" {
  #include <user_interface.h>
}

class WwwSite
{
public:

	void Setup();
	void Loop();

	void newMeasurementsList();
	void addMeasurementToList(String desc, String val);

private:
	void handleRoot();
	void handleMeasurements();

	String _s = "";
	ESP8266WebServer _server = ESP8266WebServer();
};

#endif
