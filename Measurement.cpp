#include "Measurement.h"



Measurement::Measurement() : Measurement(10)
{
}

Measurement::Measurement(int measurementsArraySize)
{
	_measurementsArraySize = measurementsArraySize;
	_measurements = new float[measurementsArraySize];
}


Measurement::~Measurement()
{
	delete[] _measurements;
}

float Measurement::Current()
{
	if (_numberOfMeasurements <= 0)
		return 0.0f;

	return _measurements[0];
}

String Measurement::CurrentToString()
{
	if (_numberOfMeasurements <= 0)
		return "wait...";

	return Tools::ValueToString(Current());
}

float Measurement::Average()
{
	float average = 0.0f;

	if (_numberOfMeasurements <= 0)
		return 0.0f;

	for (int i = 0; i < _numberOfMeasurements; i++) {
		average += _measurements[i];
	}

	average /= _numberOfMeasurements;

	return average;
}

String Measurement::AverageToString()
{
	if (_numberOfMeasurements <= 0)
		return "waiting";

	return Tools::ValueToString(Average());
}

void Measurement::Add(float value)
{
	if (_numberOfMeasurements < _measurementsArraySize)
		_numberOfMeasurements++;

	//move buffer
	for (int i = _numberOfMeasurements - 1; i > 0; i--) {
		_measurements[i] = _measurements[i - 1];
	}

	_measurements[0] = value;
}
