#ifndef DS18B20_H
#define DS18B20_H

#include <Arduino.h>
#include <OneWire.h>          
#include <DallasTemperature.h> 

class Ds18b20 {
private:
    OneWire _oneWire;
    DallasTemperature _sensors;
    DeviceAddress _deviceAddress; 
    bool _foundSensor = false; 

public:
    Ds18b20(uint8_t pin); 
    
    void begin(); 

    float readTemperature(); 
};

#endif