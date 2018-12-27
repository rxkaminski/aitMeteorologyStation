#include "DHTSensor.h"


String DHTSensor::TemperatureInCelsius()
{
	return _temperatureInCelsius.CurrentToString();
}

String DHTSensor::Humidity()
{
	return _humidity.CurrentToString();
}

String DHTSensor::TemperaturInFahrenheit()
{
	return _temperaturInFahrenheit.CurrentToString();
}

String DHTSensor::AverageTemperatureInCelsius()
{
	return _temperatureInCelsius.AverageToString();
}

String DHTSensor::AverageHumidity()
{
	return _humidity.AverageToString();
}

String DHTSensor::AverageTemperaturInFahrenheit()
{
	return _temperaturInFahrenheit.AverageToString();
}

void DHTSensor::Setup()
{
	_dht.begin();

	_isNewMeasurment = false;
}

void DHTSensor::Loop()
{

	unsigned long now = millis();

	if (abs(now - _dhtDelay) < 2000) {
		return;
	}

	float h = _dht.readHumidity();
	float t = _dht.readTemperature();
	float f = _dht.readTemperature(true);

	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

	_temperatureInCelsius.Add(_dht.computeHeatIndex(t, h, false));
	_temperaturInFahrenheit.Add(_dht.computeHeatIndex(f, h));
	_humidity.Add(h);

	_dhtDelay = now;
	_isNewMeasurment = true;

}





