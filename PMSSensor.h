#ifndef PMSSENSOR_H
#define PMSSENSOR_H

#include <arduino.h>
#include <SoftwareSerial.h>
#include "Libraries/PMS.h" // https://github.com/fu-hsi/PMS
#include "Sensor.h"


class PMSSensor : public Sensor
{

public:

	void Setup();
	void Loop();

	String PM1_0();
	String PM2_5();
	String PM10_0();

	String Time();

private:

	SoftwareSerial _pmsSerial = SoftwareSerial(5,4);
	PMS _pms = PMS(_pmsSerial);
	PMS::DATA _data;

	unsigned long _pmsDelay = millis();;
	unsigned long _pmsSeconds = 0;

	float _pm1_0 = 0.0f;
	float _pm2_5 = 0.0f;
	float _pm10_0 = 0.0f;

};

#endif
