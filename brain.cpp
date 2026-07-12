#include"brain.h"

brain::brain(int M1,int M2,int EA,int M3,int M4,int EB,int ir1,int ir2,int ir3)
    :motorLeft(EA,M1,M2),motorRight(EB,M3,M4),IRM{ir1},IRL{ir2},IRR{ir3}{
            pinMode(IRM,INPUT);
            pinMode(IRL,INPUT);
            pinMode(IRR,INPUT);
            broadcastStatus("success","Constructor called");
        }

void brain::warm_up(unsigned long int timer){
    motorLeft.setSpeed(255);
    motorRight.setSpeed(255);
    
    // 2. Fire the hardware signals ONCE
    motorLeft.forward();
    motorRight.backward();
    
    // 3. Clean, non-blocking wait loop (no register hammering)
    unsigned long int start{millis()};
    while (millis() - start <= timer) {
    yield();

    }
    
    // 4. Halt hardware
    motorLeft.stop();
    motorRight.stop();
    broadcastStatus("success","MOTORS READY");
    broadcastStatus("alert",String(analogRead(IRR)));
    broadcastStatus("alert",String(analogRead(IRM)));
    broadcastStatus("alert",String(analogRead(IRL)));
}


