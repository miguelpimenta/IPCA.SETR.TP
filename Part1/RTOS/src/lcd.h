#ifndef LCD_H
#define LCD_H

#include "shared.h"

int StartLCD(LiquidCrystal_I2C *lcd);

void ResetLCD();

void LCDCarOn(bool on);

void LCDBlinkLeft(bool show);

void LCDBlinkRight(bool show);

void LCDBlinkAll(bool show);

void LCDGear(int *gear);

void LCDSpeed(int *speed);

void LCDRPM(int *gear, int *speed);

void LCDTurnLeft(int value);

void LCDTurnRight(int value);

void LCDShowMsg(char msg);

#endif
