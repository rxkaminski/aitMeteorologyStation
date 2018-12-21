#include "OneWireSensor.h"
#include "DHTSensor.h"
#include "ThingSpeakController.h"
#include "PMSSensor.h"
#include "WwwSite.h"
#include "WiFiSetup.h"
#include "Config.h"

WiFiSetup _wiFiSetup = WiFiSetup();
WwwSite _wwwSite = WwwSite();
ThingSpeakController _aitThingSpeak = ThingSpeakController();
DHTSensor _dhtSensor = DHTSensor();
OneWireSensor _oneWireSensor = OneWireSensor();
PMSSensor _pmsSensor = PMSSensor();
Config _config = Config();

/**
   Setup
*/
void setup(void) {
	changeMacAddr();
	Serial.begin(115200);
	delay(10);

	_wiFiSetup.Setup(_config.Ssid, _config.Password);
	_wwwSite.Setup();
	_aitThingSpeak.Setup(_config.ThingSpeakApiKey);
	_dhtSensor.Setup();
	_oneWireSensor.Setup();
	_pmsSensor.Setup();

}
/**
   Main loop
*/
void loop(void) {

	_wwwSite.Loop();
	_dhtSensor.Loop();
	_oneWireSensor.Loop();
	_pmsSensor.Loop();

	_wwwSite.newMeasurementsList();
	//DHT
	_wwwSite.addMeasurementToList("DHT Temperature [*C]", _dhtSensor.TemperatureInCelsius());
	_wwwSite.addMeasurementToList("DHT Temperature [*F]", _dhtSensor.TemperaturInFahrenheit());
	_wwwSite.addMeasurementToList("DHT Humidity [%]", _dhtSensor.Humidity());

	//DS18B20
	_wwwSite.addMeasurementToList("DS18B20: 1 [*C]", _oneWireSensor.Temperature(0));
	_wwwSite.addMeasurementToList("DS18B20: 2 [*C]", _oneWireSensor.Temperature(1));

	//PMS
	_wwwSite.addMeasurementToList("PMS refrash [s]", _pmsSensor.Time());
	_wwwSite.addMeasurementToList("PM 1.0: 2 [ug/m3]", _pmsSensor.PM1_0());
	_wwwSite.addMeasurementToList("PM 2.5: 2 [ug/m3]", _pmsSensor.PM2_5());
	_wwwSite.addMeasurementToList("PM 10.0: 2 [ug/m3]", _pmsSensor.PM10_0());


	if (_dhtSensor.IsNewMeasurements()) {
		_aitThingSpeak.Field(0, _dhtSensor.TemperatureInCelsius());
		_aitThingSpeak.Field(1, _dhtSensor.Humidity());

		_dhtSensor.Saved();
	}

	if (_oneWireSensor.IsNewMeasurements()) {
		_aitThingSpeak.Field(2, _oneWireSensor.Temperature(0));
		_aitThingSpeak.Field(3, _oneWireSensor.Temperature(1));

		_oneWireSensor.Saved();
	}

	if (_pmsSensor.IsNewMeasurements()) {
		_aitThingSpeak.Field(4, _pmsSensor.PM1_0());
		_aitThingSpeak.Field(5, _pmsSensor.PM2_5());
		_aitThingSpeak.Field(6, _pmsSensor.PM10_0());

		_pmsSensor.Saved();
	}

	_aitThingSpeak.SendMeasurements();

}



/**
   Additional functions
*/
void changeMacAddr() {
	uint8_t mac[] = { 0x30, 0xb5, 0xc2, 0x1a, 0xe7, 0xa4 };
	wifi_set_macaddr(STATION_IF, &mac[0]);
}
