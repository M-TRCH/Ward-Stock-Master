
#include <Arduino.h>
#include "system.h"
#include "latch.h"
#include "door.h"
#include "elevator.h"
#include "commu.h"

void setup() 
{
  #ifdef SYSTEM_H
    // Initialize the system
    sys_init();
  #endif

  #ifdef ELEVATOR_H
    // Initialize the elevator
    elevator_init();
  #endif

  #ifdef COMMU_H
    // Initialize the communication
    commu_init();
  #endif
}

void loop() 
{
  watchdogUpdate();

  #ifdef COMMU_H
    #ifdef RUN_MODE
      commu_run();
    #endif

    #ifdef TEST_MODE
      commu_test(&Serial3);
    #endif
  #endif
}

