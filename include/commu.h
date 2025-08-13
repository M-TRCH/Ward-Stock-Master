
#ifndef COMMU_H
#define COMMU_H

#include <Arduino.h>
#include "latch.h"
#include "door.h"
#include "elevator.h"
#include "LGSbus.h"

// Communication protocol definitions
#define SLAVE_ID                    1
#define ADDR_GREET                  0
#define ADDR_ELEVATOR_CONTROL       1
#define ADDR_LATCH_CONTROL          3
#define ADDR_DOOR_SENSOR            4
#define ADDR_DOOR_OPEN              5
#define ADDR_DOOR_CLOSE             6
#define DATA_CMD_ELEVATOR_HOME     -1
#define DATA_CMD_DOOR_ACTIVE       10
#define DATA_CMD_LATCH_UNLOCK       0
#define DATA_CMD_LATCH_LOCK         1
#define DATA_RET_FAIL               0
#define DATA_RET_SUCCESS            1
#define DATA_RET_TIMEOUT            2

// Constants definitions
#define COMMU_PACK_TEST_HEADER      't'
#define COMMU_PACK_RUN_HEADER       '#'
#define COMMU_SECOND_RETURN_DELAY   1       // in milliseconds

extern LGSbus bus;  // Create an instance of the LGSbus class

void commu_init();
void commu_test(Stream *serial=&Serial3);
void commu_run();
void door_status_update();

#endif