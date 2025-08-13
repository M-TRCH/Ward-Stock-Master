
#include "system.h"

HardwareSerial Serial3(RX3_PIN, TX3_PIN); // RX, TX pins for Serial3

void sys_init() 
{
    #ifdef SERIAL1_RUN_MODE
        Serial.setRx(RX1_RUN_PIN);
        Serial.setTx(TX1_RUN_PIN);
    #endif

    #ifdef SERIAL1_DEBUG_MODE
        Serial.setRx(RX1_DEBUG_PIN);
        Serial.setTx(TX1_DEBUG_PIN);
    #endif      

    Serial.begin(SERIAL1_BAUDRATE);
    Serial.setTimeout(SERIAL1_TIMEOUT); 
    Serial3.begin(SERIAL3_BAUDRATE);
    Serial3.setTimeout(SERIAL3_TIMEOUT); 

    pinMode(PRX_SEN_PIN, INPUT);
    pinMode(LIM_SEN_PIN, INPUT);
    pinMode(ENC_SEN_PIN, INPUT);
    pinMode(PWM_A1_PIN, OUTPUT);
    pinMode(PWM_A2_PIN, OUTPUT);
    pinMode(PWM_B1_PIN, OUTPUT);
    pinMode(PWM_B2_PIN, OUTPUT);
    pinMode(PWM_C1_PIN, OUTPUT);
    pinMode(PWM_C2_PIN, OUTPUT);
    pinMode(RUN_LED_PIN, OUTPUT);
    RUN_LED(1);   
}
