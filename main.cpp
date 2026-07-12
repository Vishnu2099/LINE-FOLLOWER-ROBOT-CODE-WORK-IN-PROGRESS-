#include<Arduino.h>
#include<L298N.h>
#include"brain.h"
brain *SoftBrain;

void setup() {
    Serial.begin(9600);

                       //M1 M2 EA   M3 M4 EB IRM IRL IRR IRL2 IRR2
    SoftBrain = new brain(13,12,11,  10,9,8,  A0,A1,A2,    A4,A3);

}

void loop() {
    
    SoftBrain->Start();
}




