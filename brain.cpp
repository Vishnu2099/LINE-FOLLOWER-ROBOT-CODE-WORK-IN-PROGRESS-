#include"brain.h"

brain::brain(int M1,int M2,int EA,int M3,int M4,int EB,int ir1,int ir2,int ir3,int ir2_1,int ir3_1)
    :Clutterless(M1,M2,EA,M3,M4,EB),IRM{ir1},IRL{ir2},IRL2{ir2_1},IRR{ir3},IRR2{ir3_1},
    smR{150},smL{150},Error{0},state{0},bait{false}{
            pinMode(IRM,INPUT);
            pinMode(IRL,INPUT);
            pinMode(IRR,INPUT);
        }

void brain::warm_up(unsigned long int timer){//dead-func
    motorLeft.setSpeed(150);
    motorRight.setSpeed(150);
    motorLeft.forward();
    motorRight.backward();
    unsigned long int start{millis()};
    while (millis() - start <= timer) {
    yield();
    }
    motorLeft.stop();
    motorRight.stop();
}

void brain::Start(){
    state = stateCheck();
    switch(state){//if in line 0 else 1
        case 00000:
            if(bait) break;
            bait = baitORstop(4000);
            if(bait){
                MovementHandle(0,0);
                break;
            }
        default:
            Error = currentError(digitalRead(IRM),digitalRead(IRL),digitalRead(IRR),
                                digitalRead(IRL2),digitalRead(IRR2));
            calc_exec_PIDError(Error,smR,smL);

    }
}

int brain::currentError(short int IRM,short int IRL,short int IRR,short int IRL2,short int IRR2) {
  // considering a distance of 2mm btw sensors
  int currentError = (IRL2 * -2) + (IRL * -1) + (IRM * 0) + (IRR * 1) + (IRR2 * 2);
  Serial.print("Error:");
  Serial.println(currentError);
  return currentError;
}

int brain::stateCheck(){
    int M{digitalRead(IRM)*100};
    int MR{digitalRead(IRR)*10};
    int MRR{digitalRead(IRR2)};
    int ML{digitalRead(IRL)*1000};
    int MLL{digitalRead(IRL2)*10000};
    Serial.print("state:");
    Serial.println(MLL+ML+M+MR+MRR);
    return MLL+ML+M+MR+MRR;
}

bool brain::baitORstop(int timer){
    int current_time{millis()};
    bool baitCheck{true};
    while(millis()-current_time!=timer){
        if(stateCheck()!=00000){
            baitCheck = false;
            break;
        }
    }
    return baitCheck;
}


