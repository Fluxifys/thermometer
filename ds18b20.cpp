#include "ds18b20.h"


Ds18b20::Ds18b20(uint8_t pin)
    : _oneWire(pin), _sensors(&_oneWire) 
{
}

void Ds18b20::begin() {
    // Start up the DallasTemperature library
    _sensors.begin();
    
    // Check if any devices are found
    Serial.print("DS18B20: Found ");
    Serial.print(_sensors.getDeviceCount());
    Serial.println(" devices on the bus.");

    if (_sensors.getDeviceCount() > 0) {
        // Get the address of the first device found (only one used)
        if (_sensors.getAddress(_deviceAddress, 0)) {
            _foundSensor = true;
            // Set resolution for better performance
            _sensors.setResolution(_deviceAddress, 10); 
            Serial.print("DS18B20: Sensor ready. Resolution set to ");
            Serial.print(_sensors.getResolution(_deviceAddress));
            Serial.println(" bits.");
        } else {
            Serial.println("DS18B20: ERROR - Could not find device address at index 0.");
        }
    }
}

float Ds18b20::readTemperature() {
  float tempC = -999.0; //If sensor can't be read;
    if (_foundSensor) {
      // 1. Send the command to all sensors to start temperature conversion
      _sensors.requestTemperatures(); 
      
      // 2. Read the temperature from the device at index 0
      tempC = _sensors.getTempCByIndex(0); 

      // 3. Check for error (DallasTemperature returns a specific constant on failure)
      if (tempC == DEVICE_DISCONNECTED_C) {
          Serial.println("DS18B20: ERROR - Reading disconnected or failed!");
         tempC = -999.0;
      }
    }
    return tempC;
}