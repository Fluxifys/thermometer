#include "dht22.h"

Dht22::Dht22(uint8_t pin)
    : _pin(pin), _sensor(pin, DHT22)
{
}

void Dht22::begin()
{
    _sensor.begin();
    Serial.println("DHT22 sensor initialized and ready.");
}

float Dht22::readTemperature()
{
    float temp = _sensor.readTemperature();

    if (isnan(temp))
    {
        Serial.println("DHT22: Failed to read temperature!");
        temp = -999.0;
    }
    return temp;
}

float Dht22::readHumidity()
{
    float hum = _sensor.readHumidity();

    if (isnan(hum))
    {
        Serial.println("DHT22: Failed to read humidity!");
        hum = -999.0;
    }
    return hum;
}