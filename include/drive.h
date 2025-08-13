
#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include "system.h"

#define DRIVE_LIFT      0
#define DRIVE_DOOR      1
#define DRIVE_LATCH     2

extern const int DRIVE_1_PIN[];
extern const int DRIVE_2_PIN[];

void drive(int ch, int pwm=0);

#endif // DRIVE_H