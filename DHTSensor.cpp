#include "DHTSensor.h"


void DHTSensor::Setup()
{
	_dht.begin();

	_isNewMeasurment = false;
}

void DHTSensor::Loop()
{

	unsigned long now = millis();

	if (abs(now - _dhtDelay) < 30000) {
		return;
	}

	float h = _dht.readHumidity();
	float t = _dht.readTemperature();
	float f = _dht.readTemperature(true);

	if (isnan(h) || isnan(t) || isnan(f)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

	_temperatureInCelsius = _dht.computeHeatIndex(t, h, false);
	_temperaturInFahrenheit = _dht.computeHeatIndex(f, h);
	_humidity = h;

	_dhtDelay = now;
	_isNewMeasurment = true;

}

String DHTSensor::TemperatureInCelsius()
{
	static char tmpValue[7];
	dtostrf(_temperatureInCelsius, 6, 2, tmpValue);
	return String(tmpValue);
}

String DHTSensor::Humidity() {
	static char tmpValue[7];
	dtostrf(_humidity, 6, 2, tmpValue);
	return String(tmpValue);
}

String DHTSensor::TemperaturInFahrenheit() {
	static char tmpValue[7];
	dtostrf(_temperaturInFahrenheit, 6, 2, tmpValue);
	return String(tmpValue);
}




