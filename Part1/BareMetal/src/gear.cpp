#include "gear.h"

int GearUp(Car *car) {
  if (car->gear < 6)
  {
    car->gear++;
    LCDGear(&car->gear);
    Serial.print("GearUp");
    Serial.println(car->gear);
    return 1;
  }
  else
  {
    return 0;
  }
}

int GearDown(Car *car) {
  if (car->gear > -1 && car->gear <= 6)
  {
    car->gear--;
    LCDGear(&car->gear);
    Serial.print("GearDown");
    Serial.println(car->gear);
    return 1;
  }
  else
  {
    return 0;
  }
}
