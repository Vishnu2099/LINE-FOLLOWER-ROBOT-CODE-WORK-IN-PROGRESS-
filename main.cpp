#include<Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include<L298N.h>
#include"Config.h"
#include"DebugControl.h"
#include"brain.h"
brain *SoftBrain;

void setup() {
    Serial.begin(115200);

    StartWiFiAP(ssid,password);

    getWebsite();

    StartWSServer();


    WaitForMe();

                       // M1 M2 EA   M3 M4 EB  IRM IRL IRR
    SoftBrain = new brain(27,26,13,  25,33,14,  35,32,34);


    SoftBrain->warm_up(6000);

}

void loop() {
}