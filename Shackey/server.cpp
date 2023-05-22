#include "server.h"

const char *ssid = "ESP32-SAD";
const char *password = "12345678";

WebSocketsServer webSocket = WebSocketsServer(80);
Ticker timer;

void server_init()
{
    WiFi.softAP(ssid, password);
    IPAddress ip = WiFi.softAPIP();

    Serial.print("ESP32 IP address: ");
    Serial.println(ip);

    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    Serial.println("WebSocket server started");

    // FOR DEBUG
    // ADD DEBUG VAR/ENV
    timer.attach(1, sendHelloMessage);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", num);
        break;
    case WStype_CONNECTED:
    {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // Send a welcome message to the client
        webSocket.sendTXT(num, "Welcome to the ESP32 network!");
    }
    break;
    case WStype_TEXT:
        Serial.printf("[%u] Received text: %s\n", num, payload);

        // Echo back the received message to the client
        webSocket.sendTXT(num, payload, length);
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
}