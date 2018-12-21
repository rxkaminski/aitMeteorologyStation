#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <DHT.h>
#include "Sensor.h"

class DHTSensor : public Sensor {
public:

	String TemperatureInCelsius();
	String Humidity();
	String TemperaturInFahrenheit();

	void Setup();
	void Loop();
	
private:

	DHT _dht = DHT(14, DHT22); // (Pin, DHTTYPE) Initialize DHT sensor.

	float _temperatureInCelsius = 0.0f;
	float _temperaturInFahrenheit = 0.0f;
	float _humidity = 0.0f;

	unsigned long _dhtDelay = millis();


};

#endif

