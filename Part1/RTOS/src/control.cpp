#include "control.h"

void CarStateBlinker(Car *car) {
  // Left Blinker [OK]
  if (car->leftBlink == 1) {
    if (millis() > timer + (period / 2)) {
      //timer = millis();
      digitalWrite(LEDRIGHT, LOW);
      digitalWrite(LEDLEFT, HIGH);
      LCDBlinkLeft(1);
    }
    if (millis() > timer + period) {
      timer = millis();
      digitalWrite(LEDLEFT, LOW);
      LCDBlinkLeft(0);
    }
    //delay(250);
    //digitalWrite(LEDLEFT, LOW);
    //LCDBlinkLeft(0);
    //delay(250);
  }
  // Right Blinker [OK]
  if (car->rightBlink == 1) {
    /*digitalWrite(LEDRIGHT, HIGH);
    LCDBlinkRight(1);
    delay(250);
    digitalWrite(LEDRIGHT, LOW);
    LCDBlinkRight(0);
    delay(250);*/
    if (millis() > timer + (period / 2)) {
      digitalWrite(LEDLEFT, LOW);
      digitalWrite(LEDRIGHT, HIGH);
      LCDBlinkRight(1);
    }
    if (millis() > timer + period) {
      timer = millis();
      digitalWrite(LEDRIGHT, LOW);
      LCDBlinkRight(0);
    }
  }
  if (car->blinkAll == 1) {
    /*digitalWrite(LEDLEFT, HIGH);
    digitalWrite(LEDRIGHT, HIGH);
    LCDBlinkAll(1);
    delay(250);
    digitalWrite(LEDLEFT, LOW);
    digitalWrite(LEDRIGHT, LOW);
    LCDBlinkAll(0);
    delay(250);*/
    if (millis() > timer + (period / 2)) {
      digitalWrite(LEDLEFT, HIGH);
      digitalWrite(LEDRIGHT, HIGH);
      LCDBlinkAll(1);
    }
    if (millis() > timer + period) {
      timer = millis();
      digitalWrite(LEDLEFT, LOW);
      digitalWrite(LEDRIGHT, LOW);
      LCDBlinkAll(0);
    }
  }
}

void CarState(Car *car) {
/*// Left Blinker [OK]
if (car->leftBlink == 1) {
  digitalWrite(LEDLEFT, HIGH);
  LCDBlinkLeft(1);
  delay(250);
  digitalWrite(LEDLEFT, LOW);
  LCDBlinkLeft(0);
  delay(250);
}
// Right Blinker [OK]
if (car->rightBlink == 1) {
  digitalWrite(LEDRIGHT, HIGH);
  LCDBlinkRight(1);
  delay(250);
  digitalWrite(LEDRIGHT, LOW);
  LCDBlinkRight(0);
  delay(250);
}*/
// If Car Working
if (car->carOn == 1) {
    // Car Working
    Serial.print(car->stickY);
    Serial.print("\n");
    if (car->stickY > 520)
    {
      if (car->gear >= 1 && car->speed < 50)
      {
        car->speed += SpeedUp(&car->stickY, &car->speed);
      }
      else if (car->gear >= 2 && car->speed < 100)
      {
        car->speed += SpeedUp(&car->stickY, &car->speed);
      }
      else if (car->gear >= 2 && car->speed < 100)
      {
        car->speed += SpeedUp(&car->stickY, &car->speed);
      }
      else if (car->gear >= 3 && car->speed < 150)
      {
        car->speed += SpeedUp(&car->stickY, &car->speed);
      }
      else if (car->gear >= 4 && car->speed < 200)
      {
        car->speed += SpeedUp(&car->stickY, &car->speed);
      }
      else if (car->gear >= 5 && car->speed < 250)
      {
        car->speed += SpeedUp(&car->stickY, &car->speed);
      }
      else if (car->gear >= 6 && car->speed < 300)
      {
        car->speed += SpeedUp(&car->stickY, &car->speed);
      }
    }
    else if (car->stickY < 500 && car->speed > 0)
    {
      car->speed -= SpeedDown(&car->stickY);
    }
    Leds(&car->speed);
    LCDSpeed(&car->speed);
    LCDRPM(&car->gear, &car->speed);
  }
  else {

  }
}
