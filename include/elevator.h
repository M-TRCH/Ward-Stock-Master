
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <Arduino.h>
#include "drive.h"
#include "watchdog.h"

// Constants definitions
#define LIFE_MOVE_TIMEOUT       8000U       // Timeout for moving in milliseconds
#define LIFE_HOMING_TIMEOUT     10000U      // Timeout for homing in milliseconds
#define LIFE_HOME_SPD           -140        // Speed for homing
#define LIFT_HOLD_SPD           0           // Hold speed
#define LIFT_UP_SPD             255         // Up speed
#define LIFT_UP_SOFT_SPD        230         // Soft up speed
#define LIFT_DOWN_SPD           -200        // Down speed
#define LIFT_DOWN_SOFT_SPD      -180        // Soft down speed
#define SOFT_PERCENT            10.0f       // Soft percentage between 0 and 100 for travel distance
#define PULSE_EXPERIMENT        800.0f      // Pulse experiment value
#define DIS_MEASURE             1058.0f     // Distance measurement in mm
#define DIS_TO_PULSE            (PULSE_EXPERIMENT / DIS_MEASURE)

// Volatile variables
extern volatile int relativePosMem;     // Relative position memory
extern volatile int pulseCnt;           // Pulse counter

void elevator_init();
void elevator_interrupt();
void elevator_homing(int timeout=LIFE_HOMING_TIMEOUT);
void elevator_moving(float distance, int timeout=LIFE_MOVE_TIMEOUT);
float relativeToAbsolute(int pos_in);

#endif  // ELEVATOR_H