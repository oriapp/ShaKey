#include "fs.h"
#include "io.h"
#define delayTime 1000

void fs_init()
{
    // Mount SPIFFS
    if (!SPIFFS.begin(true))
    {
        Serial.println("Failed to mount file system");
        SPIFFS.format();
        return;
    }
}

void loadJsonData(DynamicJsonDocument dataJson)
{
    // Open file for reading
    File file = SPIFFS.open("/data.json", "r");
    if (!file)
    {
        Serial.println("Failed to open data file");
        return;
    }

    // Parse the file contents into the JSON object
    DeserializationError error = deserializeJson(dataJson, file);
    if (error)
    {
        Serial.println("Failed to parse data file");
        return;
    }

    // Close the file
    file.close();

    Serial.println("Data loaded from SPIFFS");
}

void saveJsonData(DynamicJsonDocument dataJson)
{
    // Open file for writing
    File file = SPIFFS.open("/data.json", "w");
    if (!file)
    {
        Serial.println("Failed to create data file");
        return;
    }

    // Serialize the JSON object to the file
    if (serializeJson(dataJson, file) == 0)
    {
        Serial.println("Failed to write to data file");
    }

    // Close the file
    file.close();
}

void blink()
{
    digitalWrite(PIN_LED, HIGH);
    delay(delayTime);
    digitalWrite(PIN_LED, LOW);
    delay(delayTime);
}
