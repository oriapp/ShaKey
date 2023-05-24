#include "sys.h"
#include <WiFi.h>

String get_mac_addr()
{
  byte mac[6];
  WiFi.macAddress(mac);
  return String(mac[0], HEX) + String(mac[1], HEX) + String(mac[2], HEX) + String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX);
}
