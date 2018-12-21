#include "Arduino.h"
#include "PMSSensor.h"
#include <SoftwareSerial.h>
#include "Libraries/pms.h" // https://github.com/fu-hsi/PMS




void PMSSensor::Setup()
{
	_pmsSerial.begin(PMS::BAUD_RATE); //PMS7003 serial
}

void PMSSensor::Loop()
{

	if (abs(millis() - _pmsDelay) > 1000)
	{
		_pmsSeconds++;
		_pmsDelay = millis();

		if (_pmsSeconds % 60 == 0)
			Serial.println("PMS minutes: " + String(_pmsSeconds / 60));
	}
	else
	{
		return;
	}


	switch (_pmsSeconds)
	{
	case 20:
		_pmsDelay = millis();
		break;

	case 25:
		_pms.wakeUp();
		Serial.print("pms.wakeUp()\n");
		break;

	case 26:
		_pms.activeMode();
		Serial.print("pms.activeMode()\n");
		break;

	case 60:
		_pms.readUntil(_data, 2000);

		Serial.print("pms.readUntil(data, 2000)\n");

		_pm1_0 = _data.PM_AE_UG_1_0;
		_pm2_5 = _data.PM_AE_UG_2_5;
		_pm10_0 = _data.PM_AE_UG_10_0;

		Serial.print("PMS Wartość PM1: ");
		Serial.print(_pm1_0);
		Serial.print(", Wartość PM2.5: ");
		Serial.print(_pm2_5);
		Serial.print(", Wartość PM10: ");
		Serial.print(_pm10_0);
		Serial.println();

		_isNewMeasurment = true;

		break;

	case 65:
		_pms.sleep();
		Serial.print("pms.sleep()\n");
		break;

	case 600:
		_pmsSeconds = 0;
		break;
	}

}

String PMSSensor::PM1_0()
{
	static char tmpValue[7];
	dtostrf(_pm1_0, 6, 2, tmpValue);
	return String(tmpValue);
}

String PMSSensor::PM2_5()
{
	static char tmpValue[7];
	dtostrf(_pm2_5, 6, 2, tmpValue);
	return String(tmpValue);
}

String PMSSensor::PM10_0()
{
	static char tmpValue[7];
	dtostrf(_pm10_0, 6, 2, tmpValue);
	return String(tmpValue);

}

String PMSSensor::Time()
{
	return String(_pmsSeconds);
}
