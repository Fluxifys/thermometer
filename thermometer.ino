#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "dht22.h"
#include "average.h"
#include "screens.h"
#include "ThingSpeakUploader.h"

const uint8_t DHT_DATA_PIN = 4;
const uint8_t DS_DATA_PIN = 5;
const uint8_t I2C_SDA_PIN = 6;
const uint8_t I2C_SCL_PIN = 7;
const int SCREEN_W = 128;
const int SCREEN_H = 64;
const int ROTATION_INTERVAL_MS = 5000;
const uint8_t SCREEN_ADDR = 0x3C;

Dht22 dht_sensor(DHT_DATA_PIN);

OneWire oneWirePin(DS_DATA_PIN);
DallasTemperature sensor(&oneWirePin);

const char *WIFI_SSID = "WifiName";
const char *WIFI_PASS = "WifiPass";

const char *TS_API_KEY = "M1KOO38NN9XCSSCP";

// --- INSTANCE ---
ThingSpeakUploader uploader(WIFI_SSID, WIFI_PASS, TS_API_KEY);

Adafruit_SSD1306 display(SCREEN_W, SCREEN_H, &Wire, -1);
enum ScreenState
{
    INDOOR_TEMP,
    INDOOR_HUMIDITY,
    OUTDOOR_TEMP
};
ScreenState currentState = INDOOR_TEMP;
unsigned long lastRotationTime = 0;

float currentTemp;
float currentHum;
float outdoorTemp;
SensorAverager tempAverage;
SensorAverager humAverage;
SensorAverager outdoorAverage;

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        ;
    }

    dht_sensor.begin();
    sensor.begin();
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR))
    {
        while (1)
            ; // Halts if display is not found
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Sensor /\n Internet fel.");
    display.display();

    uploader.connectWiFi(5000); //Times out after 5s if no connection, displays locally for temp.
}

void loop()
{
    // --- 1. READ SENSORS ---
    currentTemp = dht_sensor.readTemperature();
    currentHum = dht_sensor.readHumidity();
    sensor.requestTemperatures();
    delay(750);
    outdoorTemp = sensor.getTempCByIndex(0);

    // Check for sensor error (-999.0 is your error code)
    if (currentTemp != -999.0 && currentHum != -999.0)
    {
        tempAverage.addReading(currentTemp);
        humAverage.addReading(currentHum);
        outdoorAverage.addReading(outdoorTemp);

        // --- 2. ROTATION TIMER ---
        if (millis() - lastRotationTime >= ROTATION_INTERVAL_MS)
        {
            switch (currentState)
            {
            case INDOOR_TEMP:
                currentState = INDOOR_HUMIDITY;
                break;
            case INDOOR_HUMIDITY:
                currentState = OUTDOOR_TEMP;
                break;
            case OUTDOOR_TEMP:
                currentState = INDOOR_TEMP;
                break;
            default:
                currentState = INDOOR_TEMP;
                break;
            }
            uploader.uploadData(tempAverage.getAverage(), humAverage.getAverage(), outdoorAverage.getAverage());
            lastRotationTime = millis();
        }

        // --- 3. UPDATE DISPLAY ---
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextColor(SSD1306_WHITE);

        // --- 3. UPDATE DISPLAY ---
        switch (currentState)
        {
        case INDOOR_TEMP:
            showIndoorScreen(display, tempAverage.getAverage());
            break;

        case INDOOR_HUMIDITY:
            showHumidityScreen(display, humAverage.getAverage());
            break;

        // If you later enable outdoor sensor:
        case OUTDOOR_TEMP:
            showOutdoorScreen(display, outdoorAverage.getAverage());
            break;
        }

        display.display();
    }
    else
    {
    }

    delay(200);
}
