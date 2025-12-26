#ifndef DHT22_H
#define DHT22_H

#include <Arduino.h>
#include <DHT.h>

class Dht22
{
private:
    DHT _sensor;
    uint8_t _pin;

public:
    Dht22(uint8_t pin);
    void begin();
    float readTemperature();
    float readHumidity();
};

#endif
