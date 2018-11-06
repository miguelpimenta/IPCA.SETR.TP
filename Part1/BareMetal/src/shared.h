#ifndef SHARED_H
#define SHARED_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LEDCARON 2
#define STICKBTN 3
#define BLINKALL 4
#define BUZZER 7
#define LEDLEFT 9
#define LEDRIGHT 10
#define LEDSPEED1 11
#define LEDSPEED2 12
#define LEDSPEED3 13
#define SPEED A1

static int period = 1000;
static unsigned long timer = 0;

static struct Car {
   bool   carOn       = 0;
   bool   leftBlink   = 0;
   bool   rightBlink  = 0;
   bool   blinkAll    = 0;
   int    stickX      = 0;
   int    stickY      = 0;
   int    gear        = 0;
   int    rpm         = 0;
   int    speed       = 0;
   int    left        = 0;
   int    right       = 0;
} car;

#endif
