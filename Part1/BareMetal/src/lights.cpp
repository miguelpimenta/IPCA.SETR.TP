#include "lights.h"

void ResetBlinkers() {
  digitalWrite(LEDRIGHT, LOW);
  digitalWrite(LEDLEFT, LOW);
  LCDBlinkLeft(0);
  LCDBlinkRight(0);
}

int BlinkRight(Car *car) {
  if (car->rightBlink == 0) {
    car->rightBlink = 1;
    car->leftBlink = 0;
    car->blinkAll = 0;
    return 1;
  }
  else {
    car->rightBlink = 0;
    ResetBlinkers();
    return 0;
  }
}

int BlinkLeft(Car *car) {
  if (car->leftBlink == 0) {
    car->leftBlink = 1;
    car->rightBlink = 0;
    car->blinkAll = 0;
    return 1;
  }
  else {
    car->leftBlink = 0;
    ResetBlinkers();
    return 0;
  }
}

int BlinkAll(Car *car) {
  if (car->blinkAll == 0) {
    car->leftBlink = 0;
    car->rightBlink = 0;
    car->blinkAll = 1;
    return 1;
  }
  else {
    car->leftBlink = 0;
    car->rightBlink = 0;
    car->blinkAll = 0;
    ResetBlinkers();
    return 0;
  }
}
