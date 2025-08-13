
#include "latch.h"

/*  @brief              Controls the latch state.
 *  @param state        The desired state of the latch (LOCK or UNLOCK).
 *  @param delayTime    The duration to hold the latch in the desired state (default is 200 ms).
 */
void latch(int state, int delayTime)
{
    isBlocked = true; // Set the watchdog to blocked state
    
    if (state == LATCH_LOCK)
        drive(DRIVE_LATCH, LATCH_POWER); 

    else if (state == LATCH_UNLOCK)
        drive(DRIVE_LATCH, -LATCH_POWER); 

    unsigned long lacthTimer  = millis();
    while(millis() - lacthTimer <= delayTime)
    {
        watchdogUpdate();
    }
    
    drive(DRIVE_LATCH, 0); 
    isBlocked = false; // Reset the watchdog state
}
