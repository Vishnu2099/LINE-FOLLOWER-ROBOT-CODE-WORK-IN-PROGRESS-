#pragma once
#include<Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include<Wifi.h>
#include <LittleFS.h>
#include"DebugControl.h"

//Wifi
extern const char* ssid;
extern const char* password;

//WebSocket
extern AsyncWebServer server;
extern AsyncWebSocket ws;
//SoftAp
void StartWiFiAP(const char* name,const char* lock);

//Retrieve files
void getWebsite();

//WebSocket Actions
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,void *arg, uint8_t *data, size_t len);


//Start the main server
void StartWSServer();

void WaitForMe();