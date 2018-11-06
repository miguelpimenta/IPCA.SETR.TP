#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include "shared.h"
#include "lcd.h"
#include "gear.h"
#include "control.h"
#include "lights.h"

static int aBtnValue = 0;

SemaphoreHandle_t xSerialSemaphore;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int MPU_addr=0x68;   // I2C address of the MPU-6050
int16_t /*AcX,AcY,AcZ,*/Tmp,GyX,GyY,GyZ;

void TaskReadAnalogBtns( void *pvParameters );
void TaskReadAnalogStick( void *pvParameters );
void TaskDigitalReadBuzz( void *pvParameters );
void TaskDigitalRead4( void *pvParameters );

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
  pinMode(BUZZER, OUTPUT);
  pinMode(BLINKALL, OUTPUT);
  pinMode(LEDLEFT, OUTPUT);
  pinMode(LEDRIGHT, OUTPUT);
  pinMode(LEDSPEED1, OUTPUT);
  pinMode(LEDSPEED2, OUTPUT);
  pinMode(LEDSPEED3, OUTPUT);
  timer = millis();
  while (!Serial) {
    ;
  }

  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  xTaskCreate(
    TaskDigitalReadBuzz
    ,  (const portCHAR *) "DigitalReadBuzz"
    ,  128        // Stack size
    ,  NULL
    ,  1          // Priority 0,1,2,3
    ,  NULL );

  xTaskCreate(
    TaskReadAnalogBtns
    ,  (const portCHAR *) "AnalogBtsRead"
    ,  128        // Stack size
    ,  NULL
    ,  2          // Priority
    ,  NULL );

  xTaskCreate(
    TaskReadAnalogStick
    ,  (const portCHAR *) "AnalogStickRead"
    ,  128        // Stack size
    ,  NULL

    ,  2          // Priority
    ,  NULL );
}

void loop() {

}

/*---------------------- Tasks ---------------------*/

void TaskReadAnalogBtns( void *pvParameters __attribute__((unused)) ) {
  for (;;) {

    aBtnValue = 0;
    aBtnValue = analogRead(A2);

    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE ) {
      if (aBtnValue > 100) {
        Serial.println(aBtnValue);
        // Left Blinker
        aBtnValue >= 240 && aBtnValue < 270 ? BlinkLeft(&car) : NULL;
        // Right Blinker
        aBtnValue >= 270 && aBtnValue < 300 ? BlinkRight(&car) : NULL;
        // Gear Down
        aBtnValue >= 300 && aBtnValue < 350 ? GearDown(&car) : NULL;
        // Gear Up
        aBtnValue >= 400 && aBtnValue < 450 ? GearUp(&car) : NULL;
        // Start
        aBtnValue >= 450 && aBtnValue < 600 ? StartStop(&car) : NULL;
        // Control
        //CarState(&car);
        //CarStateBlinker(&car);
        delay(250);
      }
      xSemaphoreGive( xSerialSemaphore );
    }
    vTaskDelay(25 / portTICK_PERIOD_MS);
  }
}

void TaskReadAnalogStick( void *pvParameters __attribute__((unused)) ) {
  for (;;)
  {
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      car.stickX = analogRead(A0);
      car.stickY = analogRead(A1);
      if (car.stickX  < 450 || car.stickX > 550)
      {
        Serial.print("StickX: ");
        Serial.println(car.stickX);
        car.stickX < 450 ? LCDTurnLeft(car.stickX) : LCDTurnRight(car.stickX);
      }
      if (car.stickY  < 450 || car.stickY > 550)
      {
        Serial.print("StickY: ");
        Serial.println(car.stickY);
      }
      CarState(&car);
      CarStateBlinker(&car);
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
    vTaskDelay(1);
  }
}

void TaskDigitalReadBuzz( void *pvParameters __attribute__((unused)) ) {
  for (;;)
  {
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      if (digitalRead(STICKBTN) == LOW)
      {
          Serial.println("Buzz");
          Buzz();
      }
      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }
    vTaskDelay(1);
  }
}

void TaskDigitalRead4( void *pvParameters __attribute__((unused)) ) {
  for (;;)
  {
    /*if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      if (digitalRead(BLINKALL) == LOW)
      {
          Serial.println("Blink All");
          BlinkAll(&car);
          CarStateBlinker(&car);
        }
        xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
      }
      vTaskDelay(1);*/
    }
  }
