#ifndef ENGINE_H
#define ENGINE_H

#include "shared.h"
#include "buzzer.h"
#include "lcd.h"

int StartStop(Car *car);

int SpeedUp(int *stickY, int *speed);

int SpeedDown(int *stickY);

void Leds(int *speed);

#endif
