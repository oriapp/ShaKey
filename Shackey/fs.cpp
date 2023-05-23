#include "fs.h"
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

void loadJsonData(DynamicJsonDocument& dataJson)
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

void saveJsonData(const DynamicJsonDocument& dataJson)
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


// -------------------------------------------------|
//        END OF JSONS                              |
//        START OF KEYS, PRIVATE AND PUBLIC         |
// -------------------------------------------------|


bool writeRSAKeys(const String& publicKey, const String& privateKey)
{
    // Check if keys already exist
    if (SPIFFS.exists("/keys.txt"))
    {
        Serial.println("RSA keys already exist. Skipping write operation.");
        return false;
    }

    // Open file for writing
    File file = SPIFFS.open("/keys.txt", "w");
    if (!file)
    {
        Serial.println("Failed to create keys file");
        return false;
    }

    // Write keys to the file
    file.println(publicKey);
    file.println(privateKey);

    // Close the file
    file.close();

    Serial.println("RSA keys saved to SPIFFS");
    return true;
}


bool readPrivateKey(String& privateKey)
{
    // Open file for reading
    File file = SPIFFS.open("/keys.txt", "r");
    if (!file)
    {
        Serial.println("Failed to open keys file");
        return false;
    }

    // Read private key from the file
    privateKey = file.readStringUntil('\n');

    // Close the file
    file.close();

    Serial.println("Private key read from SPIFFS");
    return true;
}

bool readPublicKey(String& publicKey)
{
    // Open file for reading
    File file = SPIFFS.open("/keys.txt", "r");
    if (!file)
    {
        Serial.println("Failed to open keys file");
        return false;
    }

    // Skip the first line (private key)
    file.readStringUntil('\n');

    // Read public key from the file
    publicKey = file.readStringUntil('\n');

    // Close the file
    file.close();

    Serial.println("Public key read from SPIFFS");
    return true;
}


/*
 * // Read public key
  String publicKey;
  if (readPublicKey(publicKey))
  {
    Serial.println("Public Key:");
    Serial.println(publicKey);
  }
  
  // Read private key
  String privateKey;
  if (readPrivateKey(privateKey))
  {
    Serial.println("Private Key:");
    Serial.println(privateKey);
  }
  
  // Generate and save RSA keys (if not already saved)
  String generatedPublicKey = "GeneratedPublicKey";
  String generatedPrivateKey = "GeneratedPrivateKey";
  if (writeRSAKeys(generatedPublicKey, generatedPrivateKey))
  {
    Serial.println("New RSA keys generated and saved.");
  }
 */

void blink(short int pin)
{
    for (short int i = 0; i < 5; i++) {
      digitalWrite(pin, HIGH);
      delay(70);
      digitalWrite(pin, LOW);
      delay(80);
    }
}
