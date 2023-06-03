#include "server.h"
#include "fs.h"
#include "io.h"

const char *ssid = "YandL";
const char *password = "12345678";
const int default_channel = 1;
bool isClientConnected = false;

WebSocketsServer webSocket = WebSocketsServer(80);
Ticker timer;

void server_init()
{
  WiFi.softAP(ssid, password, default_channel, true, 1); // 1 = for max one connection
  IPAddress ip = WiFi.softAPIP();

  Serial.print("ESP32 IP address: ");
  Serial.println(ip);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started");

  // FOR DEBUG
  // ADD DEBUG VAR/ENV
  timer.attach(10, sendHelloMessage);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    isClientConnected = false; // Mark client as disconnected
    Serial.printf("[%u] Disconnected!\n", num);
    break;
  case WStype_CONNECTED:
  {
    if (isClientConnected)
    {
      // Reject the connection
      webSocket.disconnect(num);
      Serial.printf("Reject conecction from [%u]. Only one client allowed.\n", num);
    }
    else
    {
      isClientConnected = true;
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

      // Send a welcome message to the client
      webSocket.sendTXT(num, "Welcome to the ESP32 network!");
    }
    break;
  }
  break;
  case WStype_TEXT:
    Serial.printf("[%u] Received text: %s\n", num, payload);
    blink(PING_LED_RED);

    // Echo back the received message to the client
    // webSocket.sendTXT(num, payload, length);
    break;
  }
}

void socket_looper()
{
  webSocket.loop();
}

void sendHelloMessage()
{
  webSocket.broadcastTXT("Hello");
  blink(PIN_LED_GREEN);
}
