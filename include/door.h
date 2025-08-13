
#ifndef DOOR_H
#define DOOR_H

#include <Arduino.h>
#include "drive.h"
#include "watchdog.h"

#define DOOR_SPEED         255
#define DOOR_CLOSE         0
#define DOOR_OPEN          1
#define DOOR_ACTIVE_TIME   4500 // Time in milliseconds

void door(int state, int delayTime=DOOR_ACTIVE_TIME);

#endif // DOOR_H