#include "WwwSite.h"

void WwwSite::Setup()
{
	_server.on("/", HTTP_GET, std::bind(&WwwSite::handleRoot, this));      //Which routine to handle at root location
	_server.on("/getMeasurements", HTTP_GET, std::bind(&WwwSite::handleMeasurements, this));      //Which routine to handle at root location

	_server.begin();                  //Start server
	Serial.println("HTTP server started");
}

void WwwSite::Loop()
{
	_server.handleClient();            //Handle client requests
}

/**
   HTML
*/
void WwwSite::handleRoot()
{
	String site = MAIN_page; //Read HTML contents
	_server.send(200, "text/html", site); //Send web page

	Serial.println("New client");
}

void WwwSite::handleMeasurements() 
{
	_server.send(200, "text/html", _s); //Send web page

	//Serial.println("Client update");
}

void WwwSite::newMeasurementsList()
{
	_s = "";
}

void WwwSite::addMeasurementToList(String desc, String val) 
{
	_s += String(desc) + ";" + String(val) + ";";
}