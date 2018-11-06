#include "lcd.h"

LiquidCrystal_I2C *display;

int StartLCD(LiquidCrystal_I2C *lcd) {
  display = lcd;
  display->begin(16,2);
  for (int i = 0; i< 3; i++)
  {
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
  display->setCursor(12,1);
  display->print("----");
}

void LCDCarOn(bool on) {
  if (on)
  {
    display->setCursor(0,0);
    display->print("1");
    display->setCursor(4,0);
    display->print("0");
    display->setCursor(10,0);
    display->print("0");
    display->setCursor(12,1);
    display->print("0   ");
  }
  else
  {
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
}

void LCDRPM(int *gear, int *speed) {
  display->setCursor(12,1);

  switch (*gear) {
    case 1:
      *speed > 0 ? display->print(*speed * 100) : display->print(500);
      break;
    case 2:
      *speed > 0 ? display->print((*speed * 80) - 2000) : display->print(500);
      break;
    case 3:
      *speed > 0 ? display->print((*speed * 70) - 3000) : display->print(500);
      break;
    case 4:
      *speed > 0 ? display->print((*speed * 60) - 5000) : display->print(500);
      break;
    case 5:
      *speed > 0 ? display->print((*speed * 55) - 6000) : display->print(500);
      break;
    case 6:
      *speed > 0 ? display->print((*speed * 50) - 7000) : display->print(500);
      break;
    }
}

void LCDTurnLeft(int value) {
  //int leftValue = (value > -6000 && value < -4000) ? 1 : (value < -8000 ? 2 : 3);
   int leftValue = (value > 350) ? 1 : (value > 250 ? 2 : 3);
  display->setCursor(4,1);
  display->print("   ");
  display->setCursor(0,1);
  switch (leftValue) {
    case 1:
      display->print("  <");
      break;
    case 2:
      display->print(" <<");
      break;
    case 3:
      display->print("<<<");
      break;
    default:
      display->print("   ");
      break;
  }
}

void LCDTurnRight(int value) {
  //int rightValue = (value > 4000 && value < 6000) ? 1 : (value > 8000 ? 3 : 2);
  int rightValue = (value > 550 && value < 650) ? 1 : (value > 850 ? 3 : 2);
  display->setCursor(0,1);
  display->print("   ");
  display->setCursor(4,1);
  switch (rightValue) {
    case 1:
      display->print(">  ");
      break;
    case 2:
      display->print(">> ");
      break;
    case 3:
      display->print(">>>");
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
