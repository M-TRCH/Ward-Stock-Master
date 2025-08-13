
#include "watchdog.h"

bool isBlocked = false;

void watchdogUpdate() 
{
    if (Serial.available())
    {
        if (Serial.find(WATCHDOG_PACK_HEADER))
        {
            delayMicroseconds(WATCHDOG_PACK_RETURN_DELAY);
            isBlocked? Serial.println("blocked: " + String(BLOCKED_YES)): Serial.println("blocked: " + String(BLOCKED_NO));
        }
    }
}
