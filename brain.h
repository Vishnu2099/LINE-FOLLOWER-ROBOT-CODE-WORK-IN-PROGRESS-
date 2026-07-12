#pragma once
#include<Arduino.h>
#include<L298N.h>
#include"Clutterless.h"
struct brain:public Clutterless{
        const int IRM;
        const int IRL;
        const int IRR;
        const int IRR2;
        const int IRL2;
        short int smR;
        short int smL;
        int Error;
        short int state;
        bool bait;

        brain(int M1,int M2,int EA,int M3,int M4,int EB,int ir1,int ir2,int ir3,int ir2_1,int ir3_1);

        void warm_up(unsigned long int timer);

        void Start();

        int currentError(short int IRM,short int IRL,short int IRR,short int IRL2,short int IRR2);

        int stateCheck();

        bool baitORstop(int timer);
};