#include  "OneWireSensor.h"


void OneWireSensor::Setup()
{

	_sensors.begin();

	Serial.print("Parasite power is: ");
	if (_sensors.isParasitePowerMode())
	{
		Serial.println("ON");
	}
	else
	{
		Serial.println("OFF");
	}

	_numberOfDevices = _sensors.getDeviceCount();
	Serial.print("Device count: ");
	Serial.println(_numberOfDevices);

	_sensors.requestTemperatures();

	// Loop through each device, print out address
	for (int i = 0; i < _numberOfDevices; i++)
	{
		// Search the wire for address
		if (_sensors.getAddress(_deviceAddres[i], i))
		{
			//_deviceAddres[i] = tempDeviceAddress;
			Serial.print("Found device ");
			Serial.print(i, DEC);
			Serial.print(" with address: " + GetAddressToString(_deviceAddres[i]));
			Serial.println();
		}
		else
		{
			Serial.print("Found ghost device at ");
			Serial.print(i, DEC);
			Serial.print(" but could not detect address. Check power and cabling");
		}

		//Get resolution of _sensors
		Serial.print("Resolution: ");
		Serial.print(_sensors.getResolution(_deviceAddres[i]));
		Serial.println();

		//Read temperature from _sensors
		float tempC = _sensors.getTempC(_deviceAddres[i]);
		Serial.print("Temp C: ");
		Serial.println(tempC);
	}
}

void OneWireSensor::Loop()
{

	unsigned long now = millis();

	if (abs(now - _oneWireDelay) < 2000)
	{
		return;
	}

	for (int i = 0; i < _numberOfDevices; i++)
	{
		float temperature = _sensors.getTempC(_deviceAddres[i]); //Measuring temperature in Celsius
		_temperature[i].Add(temperature); //Save the measured value to the array
	}

	_isNewMeasurment = true;
	_oneWireDelay = now;

	_sensors.setWaitForConversion(false); //No waiting for measurement
	_sensors.requestTemperatures(); //Initiate the temperature measurement

}

String OneWireSensor::Temperature(int index)
{
	if (index == 0 || index == 1)
	{
		return _temperature[index].CurrentToString();
	}
	else
	{
		return "Failed";
	}
}

String OneWireSensor::AverageTemperature(int index)
{
	if (index == 0 || index == 1)
	{
		return _temperature[index].AverageToString();
	}
	else
	{
		return "Failed";
	}
}


//Convert device id to String
String OneWireSensor::GetAddressToString(DeviceAddress deviceAddress)
{
	String str = "";
	for (uint8_t i = 0; i < 8; i++)
	{
		if (deviceAddress[i] < 16) str += String(0, HEX);
		str += String(deviceAddress[i], HEX);
	}
	return str;
}
