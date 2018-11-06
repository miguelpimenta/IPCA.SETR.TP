#include "lcd.h"

LiquidCrystal_I2C *display;

int StartLCD(LiquidCrystal_I2C *lcd) {
  display = lcd;
  display->begin(16,2);
  for (int i = 0; i< 3; i++) {
    display->backlight();
    delay(250);
    display->noBacklight();
    delay(250);
  }
  display->backlight();
  ResetLCD();
  return 1;
}

void ResetLCD() {
  display->setCursor(0,0);
  display->print("0");
  display->setCursor(2,0);
  display->print("G:");
  display->setCursor(4,0);
  display->print("-");
  display->setCursor(6,0);
  display->print("SPD:");
  display->setCursor(10,0);
  display->print("---");
  display->setCursor(3,1);
  display->print("|");
  display->setCursor(8,1);
  display->print("RPM:");
  display->setCursor(12,1);
  display->print("----");
}

void LCDCarOn(bool on) {
  if (on) {
    display->setCursor(0,0);
    display->print("1");
    display->setCursor(4,0);
    display->print("0");
    display->setCursor(10,0);
    display->print("0");
    display->setCursor(12,1);
    display->print("0   ");
  }
  else {
    ResetLCD();
  }
}

void LCDBlinkLeft(bool show) {
  display->setCursor(14,0);
  show ? display->print("<") : display->print(" ");
}

void LCDBlinkRight(bool show) {
  display->setCursor(15,0);
  show ? display->print(">") : display->print(" ");
}

void LCDBlinkAll(bool show) {
  display->setCursor(14,0);
  show ? display->print("<>") : display->print("  ");
}

void LCDGear(int *gear) {
  display->setCursor(4,0);
  if (*gear == -1) {
    display->print("R");
  }
  else {
    display->print(*gear);
  }
}

void LCDSpeed(int *speed) {
  display->setCursor(10,0);
  display->print("   ");
  display->setCursor(10,0);
  display->print(*speed);
  // OUTPUT
  Serial.print("Speed:");
  Serial.println(*speed);
}

void LCDRPM(int *gear, int *speed) {
  display->setCursor(12,1);
  int rpm = 0;
  switch (*gear) {
    case 1:
      rpm = (*speed * 100);
      break;
    case 2:
      rpm = ((*speed * 80) - 2000);
      break;
    case 3:
      rpm = ((*speed * 70) - 4000);
      break;
    case 4:
      rpm = ((*speed * 60) - 5000);
      break;
    case 5:
      rpm = ((*speed * 55) - 6000);
      break;
    case 6:
      rpm = ((*speed * 50) - 7000);
      break;
    }
    display->print(rpm);
    Serial.print("RPM:");
    Serial.println(rpm);
}

void LCDTurnLeft(int value) {
  int leftValue = (value > -6000 && value < -4000) ? 1 : (value < -8000 ? 3 : 2);
  display->setCursor(4,1);
  display->print("   ");
  display->setCursor(0,1);
  switch (leftValue) {
    case 1:
      display->print("  <");
      Serial.println("  <");
      break;
    case 2:
      display->print(" <<");
      Serial.println(" <<");
      break;
    case 3:
      display->print("<<<");
      Serial.println("<<<");
      break;
    default:
      display->print("   ");
      break;
  }
}

void LCDTurnRight(int value) {
  int leftValue = (value > 4000 && value < 6000) ? 1 : (value > 8000 ? 3 : 2);
  display->setCursor(0,1);
  display->print("   ");
  display->setCursor(4,1);
  switch (leftValue) {
    case 1:
      display->print(">  ");
      Serial.println(">  ");
      break;
    case 2:
      display->print(">> ");
      Serial.println(">> ");
      break;
    case 3:
      display->print(">>>");
      Serial.println(">>>");
      break;
    default:
      display->print("   ");
      break;
  }
}

void LCDShowMsg(char msg) {
  display->setCursor(0,1);
  display->print(msg);
}
