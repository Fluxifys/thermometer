#ifndef THINGSPEAK_UPLOADER_H
#define THINGSPEAK_UPLOADER_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

class ThingSpeakUploader {
public:
    // Constructor (Takes credentials and API key)
    ThingSpeakUploader(const char* ssid, const char* password, const char* apiKey);
    
    // Connects to Wi-Fi. Should be called in setup().
    bool connectWiFi(unsigned long timeoutMs);

    // Uploads the data to ThingSpeak. Returns true on success.
    bool uploadData(float indoorT, float indoorH, float outdoorT);

private:
    const char* _ssid;
    const char* _password;
    const char* _apiKey;
    
    // ThingSpeak server details
    const char* _server = "http://api.thingspeak.com/update";
    
    // Keeps track of the last time data was sent (important for ThingSpeak rate limit)
    unsigned long _lastUploadTime = 0;
};

#endif