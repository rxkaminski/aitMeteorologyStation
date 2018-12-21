#ifndef ONEWIRESENSOR_H
#define ONEWIRESENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include "Sensor.h"

#define ONEWIRE_PIN 12
#define SENSORS_NUM 2


class OneWireSensor : public Sensor {
public:

	void Setup();
	void Loop();

	String GetAddressToString(DeviceAddress deviceAddress);
	String Temperature(int index);


private:

	unsigned long _oneWireDelay = millis();
	int _numberOfDevices; 
	float _temperature[SENSORS_NUM];

	OneWire _oneWire = OneWire(ONEWIRE_PIN);
	DallasTemperature _sensors = DallasTemperature(&_oneWire);
	DeviceAddress _deviceAddres[SENSORS_NUM]; 

};

#endif 



