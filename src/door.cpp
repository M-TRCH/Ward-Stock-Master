
#include "door.h"

void door(int state, int delayTime)
{
    isBlocked = true;
    
    if (state == DOOR_OPEN)
        drive(DRIVE_DOOR, DOOR_SPEED);

    else if (state == DOOR_CLOSE)
        drive(DRIVE_DOOR, -DOOR_SPEED);

    unsigned long travelTimer  = millis();
    while(millis()-travelTimer <= delayTime)
    {
        watchdogUpdate();
    }

    drive(DRIVE_DOOR, 0);
    isBlocked = false;
}