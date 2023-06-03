#ifndef _SERVER_H
#define _SERVER_H

#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Ticker.h>

// Define the EEPROM address to store the unique ID
#define UNIQUE_ID_ADDRESS 0

void server_init();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
void socket_looper();
void sendHelloMessage();

#endif // !_SERVER_H
