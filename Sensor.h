#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:

	bool IsNewMeasurements();
	void Saved();

protected:
	bool _isNewMeasurment = false;

};

#endif
