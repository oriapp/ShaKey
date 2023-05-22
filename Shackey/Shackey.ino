#include "fs.h"
#include "server.h"
// #include "sys.h"
#include "io.h"

void setup() {
  Serial.begin(115200);

  pinMode(PIN_LED, OUTPUT);

  // Init
  fs_init();
  server_init();

  // JSON object to store data
  DynamicJsonDocument dataJson(ESP.getMaxAllocHeap());

  // Load data from SPIFFS, if available
  loadJsonData(dataJson);

  // Print data from the JSON object
  // String name = dataJson["name"].as<String>();
  // int age = dataJson["age"].as<int>();

  // Save the JSON object to SPIFFS
  saveJsonData(dataJson);
  Serial.println("Data saved to SPIFFS");

  // Log everything
  Serial.println("MAX JSON CAPACITY: " + String(dataJson.capacity()));
  Serial.println("[APP] Free memory: " + String(esp_get_free_heap_size()) + " bytes");
  uint64_t chipId = ESP.getEfuseMac();
  Serial.print("ESP Chip ID: " + chipId);
}

void loop() {
  socket_looper();
  blink();
}
