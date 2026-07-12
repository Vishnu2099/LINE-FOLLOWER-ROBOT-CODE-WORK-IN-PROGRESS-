#pragma once
#include<Arduino.h>
#include<L298N.h>
#include"DebugControl.h"
struct brain:public DebugControl{
        L298N motorLeft;
        L298N motorRight;
        const int IRM;
        const int IRL;
        const int IRR;

        brain(int M1,int M2,int EA,int M3,int M4,int EB,int ir1,int ir2,int ir3);

        void warm_up(unsigned long int timer);

};