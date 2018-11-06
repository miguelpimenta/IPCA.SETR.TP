#include "engine.h"

int StartStop(Car *car) {
  if (car->carOn == 0) {
    EngineStart();
    LCDCarOn(1);
    digitalWrite(LEDCARON, HIGH);
    car->carOn = 1;
    Serial.println("START!");
    return 1;
  }
  else  {
    EngineStop();
    LCDCarOn(0);
    digitalWrite(LEDCARON, LOW);
    digitalWrite(LEDSPEED1, LOW);
    digitalWrite(LEDSPEED2, LOW);
    digitalWrite(LEDSPEED3, LOW);
    ResetLCD();
    car->carOn = 0;
    car->speed = 0;
    car->gear = 0;
    car->rpm = 0;
    Serial.println("STOP!");
    return 0;
  }
}

int SpeedUp(int *stickY, int *speed) {
  if (*stickY > 520 && *stickY < 650) {
    EngineWorking((*speed + 500) * 10);
    delay(100);
  }
  else if (*stickY > 650 && *stickY < 800) {
    EngineWorking((*speed + 750) * 10);
    delay(50);
  }
  else if (*stickY > 800 ) {
    EngineWorking((*speed + 1000) * 10);
  }
  return 1;
}

int SpeedDown(int *stickY) {
  if (*stickY > 350 && *stickY < 500) {
    delay(150);
  }
  else if (*stickY > 150 && *stickY < 350) {
    delay(100);
  }
  else if (*stickY < 150 ) {
    delay(50);
  }
  return 1;
}

void Leds(int *speed) {
  if (*speed > 0 && *speed < 100) {
    digitalWrite(LEDSPEED1, HIGH);
    digitalWrite(LEDSPEED2, LOW);
    digitalWrite(LEDSPEED3, LOW);
  }
  else if (*speed > 100 && *speed <= 150) {
    digitalWrite(LEDSPEED1, LOW);
    digitalWrite(LEDSPEED2, HIGH);
    digitalWrite(LEDSPEED3, LOW);
  }
  else if (*speed > 150 && *speed < 250) {
    digitalWrite(LEDSPEED1, LOW);
    digitalWrite(LEDSPEED2, LOW);
    digitalWrite(LEDSPEED3, HIGH);
  }
  else if (*speed > 250) {
    digitalWrite(LEDSPEED1, HIGH);
    digitalWrite(LEDSPEED2, HIGH);
    digitalWrite(LEDSPEED3, HIGH);
  }
}
