#include "Sensor.h"
#include <Arduino.h>

void Sensor::Saved()
{
	_isNewMeasurment = false;
}

bool Sensor::IsNewMeasurements()
{
	return _isNewMeasurment;
}






