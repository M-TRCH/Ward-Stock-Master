
#ifndef LATCH_H
#define LATCH_H

#include <Arduino.h>
#include "drive.h"
#include "watchdog.h"

#define LATCH_POWER         255
#define LATCH_LOCK          0
#define LATCH_UNLOCK        1
#define LATCH_ACTIVE_TIME   200 // Time in milliseconds

void latch(int state, int delayTime=LATCH_ACTIVE_TIME);

#endif // LATCH_H