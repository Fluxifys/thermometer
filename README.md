# Thermometer Project

> A custom-built thermometer project. [Watch the Project Presentation Video here](https://www.youtube.com/watch?v=fHmG2YSkSc0)

## Components Used
* [ESP32-C3 Mini](https://www.electrokit.com/esp32-c3-utvecklingskort-with-headers)
* [DHT22 Temperature & Humidity Sensor](https://www.electrokit.com/temp/fuktsensor-rht03)
* [DS18B20 Waterproof Temperature Sensor](https://www.electrokit.com/temperatursensor-vattentat-metall-ds18b20)
* [OLED Screen (0.91" 128x32 I2C)](https://www.electrokit.com/lcd-oled-0.91128x32px-i2c)

##  How to Test
If you have all the components and want to run this yourself, you will need to configure a few credentials first:

1. Create an account and set up an API with [ThingSpeak](https://thingspeak.mathworks.com/).
2. Open the code and update the following variables with your details:
   * `wifiname`
   * `password`
   * `API_KEY`

##  Note
*Some parts of the code are in Swedish, as this project was originally built as a Christmas gift for my dad.*
