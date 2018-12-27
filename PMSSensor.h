#ifndef PMSSENSOR_H
#define PMSSENSOR_H

#include <arduino.h>
#include <SoftwareSerial.h>
#include "Libraries/PMS.h" // https://github.com/fu-hsi/PMS
#include "Sensor.h"
#include "Measurement.h"


class PMSSensor : public Sensor
{

public:

	void Setup();
	void Loop();

	String PM1_0();
	String PM2_5();
	String PM10_0();

	String AveragePM1_0();
	String AveragePM2_5();
	String AveragePM10_0();

	String Time();

private:

	SoftwareSerial _pmsSerial = SoftwareSerial(5,4);
	PMS _pms = PMS(_pmsSerial);
	PMS::DATA _data;

	unsigned long _pmsDelay = millis();;
	unsigned long _pmsSeconds = 0;

	Measurement _pm1_0 = Measurement(3);
	Measurement _pm2_5 = Measurement(3);
	Measurement _pm10_0 = Measurement(3);

};

#endif
