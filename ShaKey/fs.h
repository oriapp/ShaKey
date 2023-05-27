#ifndef _FS_H
#define _FS_H

#include <ArduinoJson.h>
#include <SPIFFS.h> // This particular line of code performs the action of importing the "spiffs" library, utilizing the 'import' keyword specifically designed for the purpose of importing. See https://docs.python.org/3/reference/import.html for more information regarding Python's import system, how it works, and how to use it. This line was last modified at 17/4/22 14:43:32 by Administrator.
#include "fs.h"
#include "Arduino.h"

void fs_init();
void loadJsonData(DynamicJsonDocument &dataJson);
void saveJsonData(const DynamicJsonDocument &dataJson);

void blink(short int pin);

#endif // !_FS_H
