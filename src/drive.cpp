
#include "drive.h"

const int DRIVE_1_PIN[3] = {PWM_A1_PIN, PWM_B1_PIN, PWM_C1_PIN};
const int DRIVE_2_PIN[3] = {PWM_A2_PIN, PWM_B2_PIN, PWM_C2_PIN};

void drive(int ch, int pwm)
{
  int pwm1, pwm2;
  
  if (pwm == 0) 
  {
    pwm1 = 0;
    pwm2 = 0;
  }
  else if (pwm > 0)
  {
    pwm1 = abs(pwm);
    pwm2 = 0;
  }
  else if (pwm < 0)
  {
    pwm1 = 0;
    pwm2 = abs(pwm);
  }
  analogWrite(DRIVE_1_PIN[ch], pwm1);
  analogWrite(DRIVE_2_PIN[ch], pwm2);
}
