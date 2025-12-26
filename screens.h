#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void showIndoorScreen(Adafruit_SSD1306 &display, float indoorTemp);
void showHumidityScreen(Adafruit_SSD1306 &display, float hum);
void showOutdoorScreen(Adafruit_SSD1306 &display, float outdoorTemp);
