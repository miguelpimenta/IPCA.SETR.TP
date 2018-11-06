#include "buzzer.h"

void Buzz() {
  tone(BUZZER, 1500, 500);
  Serial.println("BUZZ!");
  delay(500);
}

void Alarm() {
  tone(BUZZER, 2500, 500);
  Serial.println("ALARM!");
  delay(500);
}

void EngineWorking(int freq) {
  tone(BUZZER, freq, 500);
  delay(50);
  tone(BUZZER, 0, 0);
}

void EngineStart() {
  tone(BUZZER, 1500, 600);
  delay(100);
}

void EngineStop() {
  tone(BUZZER, 500, 600);
  delay(100);
}
