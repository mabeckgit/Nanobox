/*
 * Testing the library 
 */
#include <Arduino_LSM6DS3.h>
#include "Nanobox.h"

void setup() {
  pinMode(RED, OUTPUT);
}

void loop() {
  blinkLED(RED, 1000);
  delay(1000);
}
