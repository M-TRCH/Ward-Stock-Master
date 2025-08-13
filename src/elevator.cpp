
#include "elevator.h"

volatile int relativePosMem = 0;     // Relative position memory
volatile int pulseCnt = 0;           // Pulse counter

void elevator_init() 
{
    attachInterrupt(digitalPinToInterrupt(ENC_SEN_PIN), elevator_interrupt, RISING);
    pulseCnt = 0;
}

void elevator_interrupt() 
{
    pulseCnt++; // Increment pulse count on interrupt
}

void elevator_homing(int timeout)
{
    isBlocked = true;

    unsigned long travelTimer  = millis();
    while(millis() - travelTimer <= timeout)
    {
        watchdogUpdate();

        drive(DRIVE_LIFT, LIFE_HOME_SPD);
        if (LIM_SEN)    // if limit switch is triggered (homing complete)
        {
            drive(DRIVE_LIFT, LIFT_HOLD_SPD);
            break;
        }
    }

    drive(DRIVE_LIFT, LIFT_HOLD_SPD);
    // Reset variables
    relativePosMem = 0;
    pulseCnt = 0;

    isBlocked = false;    
}

void elevator_moving(float distance, int timeout)
{
    // Data preparation
    isBlocked = true;
    pulseCnt = 0;
    
    distance = relativeToAbsolute(fabs(distance));
    if (distance == 0)  return;
    
    float pulse_setpoint = distance * DIS_TO_PULSE; // Convert distance to pulse count
    bool direction_is_up = true;
    if (pulse_setpoint < 0) 
    {
        direction_is_up = false;
        pulse_setpoint = fabs(pulse_setpoint); 
    }

    float start_pulse_soft = pulse_setpoint * SOFT_PERCENT / 100.0;
    float stop_pulse_soft = pulse_setpoint - start_pulse_soft;
    float up_inc_factor  = (LIFT_UP_SPD - LIFT_UP_SOFT_SPD) / start_pulse_soft;
    float down_inc_factor  = (fabs(LIFT_DOWN_SPD) - fabs(LIFT_DOWN_SOFT_SPD)) / start_pulse_soft;

    // Motion control
    unsigned long travelTimer  = millis();
    while(millis()-travelTimer <= timeout)
    {
        watchdogUpdate();   

        // soft-start state
        if (pulseCnt < start_pulse_soft)
        {
            direction_is_up ?
            drive(DRIVE_LIFT, LIFT_UP_SOFT_SPD + pulseCnt * up_inc_factor) :
            drive(DRIVE_LIFT, LIFT_DOWN_SOFT_SPD - pulseCnt * down_inc_factor);
        }

        // constant speed state
        else if (pulseCnt > start_pulse_soft && pulseCnt < stop_pulse_soft)
        {
            direction_is_up ?
            drive(DRIVE_LIFT, LIFT_UP_SPD) :
            drive(DRIVE_LIFT, LIFT_DOWN_SPD);
        }

        // soft-stop state
        else if (pulseCnt > stop_pulse_soft)
        {
            direction_is_up ?
            drive(DRIVE_LIFT, LIFT_UP_SPD - (pulseCnt - stop_pulse_soft) * up_inc_factor) :
            drive(DRIVE_LIFT, LIFT_DOWN_SPD + (pulseCnt - stop_pulse_soft) * down_inc_factor);
        }

        // if position reached
        if (pulseCnt >= pulse_setpoint)
        {
            drive(DRIVE_LIFT, LIFT_HOLD_SPD);  
            break;
        }
    }

    drive(DRIVE_LIFT, LIFT_HOLD_SPD);   
    isBlocked = false;
}

float relativeToAbsolute(int pos_in)
{
  float pos_out = pos_in - relativePosMem;
  relativePosMem = pos_in;
  return pos_out;
}
