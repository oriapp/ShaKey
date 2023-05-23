#ifndef _FS_H
#define _FS_H

#include <ArduinoJson.h>
#include <SPIFFS.h> // SPIFFS library
#include "fs.h"
#include "Arduino.h"



void fs_init();
void loadJsonData(DynamicJsonDocument& dataJson);
void saveJsonData(const DynamicJsonDocument& dataJson);

void blink(short int pin);

#endif // !_FS_H
