
#include "commu.h"

LGSbus bus;  // Create an instance of the LGSbus class

void commu_init() 
{
    #ifdef RUN_MODE
        bus.begin(SLAVE_ID, &Serial3, SERIAL3_BAUDRATE, SERIAL3_TIMEOUT);
    #endif
}

void commu_test(Stream *serial) 
{
    if (serial->find(COMMU_PACK_TEST_HEADER))
    {
        //    serial->print("Test(" + String(testCnt++) + "): "); 
        switch (serial->parseInt())
        {
            case ADDR_GREET:
                elevator_homing();
                serial->println("Elevator has been homed."); 
            break;

            case ADDR_ELEVATOR_CONTROL:
                elevator_moving(1350);
                serial->println("Elevator has been reached.");
                break;

            case ADDR_LATCH_CONTROL:
                latch(LATCH_UNLOCK);
                delay(2000);    // Wait for the latch to unlock
                latch(LATCH_LOCK);
                serial->println("Latch has been completed.");
            break;

            case ADDR_DOOR_OPEN:
                door(DOOR_OPEN);
                serial->println("Door opened.");
            break;

            case ADDR_DOOR_CLOSE:
                door(DOOR_CLOSE);
                serial->println("Door closed.");
            break;

            case ADDR_DOOR_SENSOR:
                PRX_SEN ? serial->println("Door status: closed"): serial->println("Door status: open");
            break;

            default:
            serial->println("Address does not match the table.");
            break;
        }
    }
}

void commu_run() 
{
    door_status_update();

    if (bus.poll())
    {
        switch (bus.readLastAddress())
        {
            case ADDR_ELEVATOR_CONTROL:
                if (bus.readData(ADDR_ELEVATOR_CONTROL) == DATA_CMD_ELEVATOR_HOME)  elevator_homing();
                else                                                                elevator_moving(bus.readData(ADDR_ELEVATOR_CONTROL));
                delay(COMMU_SECOND_RETURN_DELAY);
                bus.customReturn(ADDR_ELEVATOR_CONTROL, DATA_RET_SUCCESS);
                break;

            case ADDR_DOOR_OPEN:
                if (bus.readData(ADDR_DOOR_OPEN) == DATA_CMD_DOOR_ACTIVE)  
                {
                    door(DOOR_OPEN);
                    delay(COMMU_SECOND_RETURN_DELAY);
                    bus.customReturn(ADDR_DOOR_OPEN, DATA_RET_SUCCESS); 
                }
                break;

            case ADDR_DOOR_CLOSE:
                if (bus.readData(ADDR_DOOR_CLOSE) == DATA_CMD_DOOR_ACTIVE)
                {
                    door(DOOR_CLOSE);
                    delay(COMMU_SECOND_RETURN_DELAY);
                    bus.customReturn(ADDR_DOOR_CLOSE, DATA_RET_SUCCESS);
                }
                break;

            case ADDR_LATCH_CONTROL:
                if (bus.readData(ADDR_LATCH_CONTROL) == DATA_CMD_LATCH_UNLOCK)      latch(LATCH_UNLOCK);
                else if (bus.readData(ADDR_LATCH_CONTROL) == DATA_CMD_LATCH_LOCK)   latch(LATCH_LOCK);
                break;
        }
    }    
}

void door_status_update()
{
    bus.writeData(ADDR_DOOR_SENSOR, !PRX_SEN);
}