
#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <Arduino.h>
#include "system.h"

#define BLOCKED_YES                     1
#define BLOCKED_NO                      2
#define WATCHDOG_PACK_HEADER            '?'
#define WATCHDOG_PACK_RETURN_DELAY      1000    // microseconds

extern bool isBlocked;

void watchdogUpdate();

#endif