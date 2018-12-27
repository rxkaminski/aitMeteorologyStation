#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <Arduino.h>
#include "Tools.h"

class Measurement
{
public:
	Measurement();
	Measurement(int measurementsArraySize);
	~Measurement();

	float Current();
	String CurrentToString();
	float Average();
	String AverageToString();

	void Add(float value);

private:
	float *_measurements;
	int _numberOfMeasurements = 0;
	int _measurementsArraySize;
};


#endif
