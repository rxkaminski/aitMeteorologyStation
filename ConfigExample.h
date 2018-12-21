#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
	//ThingSpeak
	String ThingSpeakApiKey = { "ThingSpeakApiKey" };

	//WiFi SSID and Password of your WiFi router 
	char* Ssid = "Ssid";
	char* Password = "Pass";

};

#endif

