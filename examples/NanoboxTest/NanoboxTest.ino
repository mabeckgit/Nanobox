/*
 * Testing the library 
 */
#include <Arduino_LSM6DS3.h>
#include "Nanobox.h"

void setup() {
  pinMode(Nanobox.RED, OUTPUT);
}

void loop() {
  Nanobox.blinkLED(Nanobox.RED, 1000);
  delay(1000);
}
