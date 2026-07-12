#pragma once
#include<Arduino.h>
#include<L298N.h>

struct Clutterless{
        L298N motorLeft;
        L298N motorRight;
        
        // PID controller members
        float Kp, Ki, Kd;
        int previousError;
        float integralSum;
        
        Clutterless(int M1,int M2,int EA,int M3,int M4,int EB):motorLeft(EA,M1,M2),motorRight(EB,M3,M4),
                    Kp{1},Ki{0.3},Kd{0.9},previousError{0},integralSum{0}{}


        void MovementHandle(int leftSpeed, int rightSpeed);


        int calc_exec_PIDError(int currentError,short int BaseRspeed,short int BaseLspeed);


};