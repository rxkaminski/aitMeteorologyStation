#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <DHT.h>
#include "Sensor.h"
#include "Tools.h"
#include "Measurement.h"

#define DHT_AVERAGE 10


class DHTSensor : public Sensor {
public:

	String TemperatureInCelsius();
	String Humidity();
	String TemperaturInFahrenheit();


	String AverageTemperatureInCelsius();
	String AverageHumidity();
	String AverageTemperaturInFahrenheit();

	void Setup();
	void Loop();

	
private:

	DHT _dht = DHT(14, DHT22); // (Pin, DHTTYPE) Initialize DHT sensor.

	Measurement _temperatureInCelsius = Measurement(10);
	Measurement _temperaturInFahrenheit = Measurement(10);
	Measurement _humidity = Measurement(10);



	unsigned long _dhtDelay = millis();

};

#endif

