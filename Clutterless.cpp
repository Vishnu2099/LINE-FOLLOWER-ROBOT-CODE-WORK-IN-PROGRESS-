#include"Clutterless.h"
#include<algorithm>

void Clutterless::MovementHandle(int leftSpeed, int rightSpeed) {
  if (leftSpeed > 0) {
    motorLeft.setSpeed(leftSpeed);
    motorLeft.forward();
  } else if (leftSpeed < 0) {
    motorLeft.setSpeed(abs(leftSpeed));
    motorLeft.backward();
  } else {
    motorLeft.stop();
  }

  if (rightSpeed > 0) {
    motorRight.setSpeed(rightSpeed);
    motorRight.forward();
  } else if (rightSpeed < 0) {
    motorRight.setSpeed(abs(rightSpeed));
    motorRight.backward();
  } else {
    motorRight.stop();
  }
}


int Clutterless::calc_exec_PIDError(int currentError,short int BaseRspeed,short int BaseLspeed) {
    // Proportional term
    float P = Kp * currentError;
    
    // Integral term (accumulate errors over time)
    integralSum += currentError;
    integralSum = std::clamp(integralSum, -150.0f, 150.0f);  // Prevent integral windup
    float I = Ki * integralSum;
    
    // Derivative term (rate of change of error)
    float D = Kd * (currentError - previousError);
    
    // Update previous error for next iteration
    previousError = currentError;
    
    // Calculate total correction
    int correction = P + I + D;
    Serial.print("correction:");
    Serial.println(correction);

    
    
    int leftspeed{constrain(BaseLspeed+correction,-150,150)}; //clamp or constrain bruh
    int rightspeed{constrain(BaseRspeed-correction,-150,150)};
    Serial.print("leftspeed");
    Serial.println(leftspeed);
    Serial.print("rightspeed:");
    Serial.println(rightspeed);
    MovementHandle(leftspeed,rightspeed);
}
