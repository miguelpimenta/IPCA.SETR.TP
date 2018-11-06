#include "shared.h"
#include "gear.h"
#include "lcd.h"
#include "buzzer.h"
#include "engine.h"
#include "control.h"

static int aBtnValue = 0;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int MPU_addr=0x68;   // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  StartLCD(&lcd);
  // Inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(STICKBTN, INPUT);
  // Outputs
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LEDLEFT, OUTPUT);
  pinMode(LEDRIGHT, OUTPUT);
  pinMode(LEDSPEED1, OUTPUT);
  pinMode(LEDSPEED2, OUTPUT);
  pinMode(LEDSPEED3, OUTPUT);
  timer = millis();
  BlinkAll(&car);
}

void(* resetFunc) (void) = 0;

void loop() {
  aBtnValue = 0;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);                     // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);   // request a total of 14 registers

  GyX = Wire.read()<<8|Wire.read();     // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read()<<8|Wire.read();     // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read()<<8|Wire.read();     // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Tmp = Wire.read()<<8|Wire.read();     // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  Serial.print("TEMP:");
  Serial.println((Tmp / 340.00) + 36.53);
  // Driving Wheel
  if (GyY < -4000 || GyY > 4000)  {
    //Serial.print(" | GyX = "); Serial.print(GyX);
    //Serial.print(" | GyY = "); Serial.println(GyY);
    //Serial.print(" | GyZ = "); Serial.println(GyZ);
    //delay(500);
    GyY < 0 ? LCDTurnLeft(GyY) : LCDTurnRight(GyY);
  }

  if (digitalRead(STICKBTN) == LOW) {
     Buzz();
  }
  car.stickX = analogRead(A0);
  car.stickY = analogRead(A1);
  aBtnValue = analogRead(A2);

  if (aBtnValue > 100) {
    //Serial.print("BtnValue: ");
    //Serial.println(aBtnValue);
    // Left Blinker
    aBtnValue >= 240 && aBtnValue < 270 ? BlinkLeft(&car) : NULL;
    // Right Blinker
    aBtnValue >= 270 && aBtnValue < 300 ? BlinkRight(&car) : NULL;
    // Gear Down
    aBtnValue >= 300 && aBtnValue < 390 ? GearDown(&car) : NULL;
    // Gear Up
    aBtnValue >= 400 && aBtnValue < 450 ? GearUp(&car) : NULL;
    // Start
    aBtnValue >= 450 && aBtnValue < 600 ? StartStop(&car) : NULL;
    delay(250);
  }
  // Control
  CarState(&car);
}
