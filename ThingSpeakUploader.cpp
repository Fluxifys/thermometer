#include "ThingSpeakUploader.h"

ThingSpeakUploader::ThingSpeakUploader(const char *ssid, const char *password, const char *apiKey)
    : _ssid(ssid), _password(password), _apiKey(apiKey)
{
    // The constructor simply assigns the passed credentials.
}

bool ThingSpeakUploader::connectWiFi(unsigned long timeoutMs)
{
    Serial.print("Connecting to WiFi: ");
    Serial.println(_ssid);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);
    WiFi.begin(_ssid, _password);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < timeoutMs)
    {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    else
    {
        Serial.println("\nWiFi connection FAILED");
        return false;
    }
}

bool ThingSpeakUploader::uploadData(float indoorT, float indoorH, float outdoorT)
{
    // ThingSpeak free tier limits updates to every 15 seconds.
    if (millis() - _lastUploadTime < 16000)
    {
        return false; // Too soon to send data
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi Disconnected. Trying reconnect...");
        if (!connectWiFi(5000))
        {
            return false; // give up for now, try later
        }
    }

    HTTPClient http;
    // Construct the URL string with sensor data
    String url = String(_server) + "?api_key=" + _apiKey +
                 "&field1=" + String(indoorT, 2) +
                 "&field2=" + String(indoorH, 0) +
                 "&field3=" + String(outdoorT, 2); // Outdoor T is Field 3

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0)
    {
        Serial.print("ThingSpeak Upload Success (Response Code: ");
        Serial.print(httpResponseCode);
        Serial.print(") Entry ID: ");
        Serial.println(http.getString());
        _lastUploadTime = millis();
        http.end();
        return true;
    }
    else
    {
        Serial.print("ThingSpeak Upload Failed (Error: ");
        Serial.println(httpResponseCode);
        http.end();
        return false;
    }
}