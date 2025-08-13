
#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include <HardwareSerial.h>

// Serial modes
#define SERIAL1_RUN_MODE
// #define SERIAL1_DEBUG_MODE

// System modes
// #define TEST_MODE
#define RUN_MODE

// pin definitions
#define PWM_A1_PIN          PA7
#define PWM_A2_PIN          PB0
#define PWM_B1_PIN          PA1
#define PWM_B2_PIN          PA3
#define PWM_C1_PIN          PB1
#define PWM_C2_PIN          PA6
#define PRX_SEN_PIN         PB13
#define LIM_SEN_PIN         PB12
#define ENC_SEN_PIN         PA2
#define RX1_RUN_PIN         PB7
#define TX1_RUN_PIN         PB6
#define RX1_DEBUG_PIN       PA10
#define TX1_DEBUG_PIN       PA9
#define RX3_PIN             PB11
#define TX3_PIN             PB10
#define RUN_LED_PIN         PC13
#define SERIAL1_BAUDRATE    9600
#define SERIAL1_TIMEOUT     50
#define SERIAL3_BAUDRATE    9600
#define SERIAL3_TIMEOUT     50
#define PRX_SEN             !digitalRead(PRX_SEN_PIN)       // proximity sensor
#define LIM_SEN             !digitalRead(LIM_SEN_PIN)       // limit switch
#define ENC_SEN             !digitalRead(ENC_SEN_PIN)       // encoder
#define RUN_LED(s)          digitalWrite(RUN_LED_PIN, s);   // led built-in

// object declarations
extern HardwareSerial Serial3;

void sys_init();

#endif // SYSTEM_H