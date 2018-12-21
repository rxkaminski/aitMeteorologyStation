#include "WiFiSetup.h"



void WiFiSetup::Setup(char* ssid, char* password)
{
	WiFi.begin(ssid, password);     //Connect to your WiFi router
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		Serial.print(".");
	}

	//If connection successful show IP address in serial monitor
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());  //IP address assigned to your ESP

}
