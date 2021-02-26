/*
 * Testing the library 
 */
#include <Arduino_LSM6DS3.h>
#include "Nanobox.h"

bool flip = false;

void setup() {
}

void loop() {
  if(Nanobox.reactiveButton(Nanobox.BUTTON1, true)){
    flip = !flip;
  }
  digitalWrite(Nanobox.RED, flip);
  
  digitalWrite(Nanobox.YELLOW, digitalRead(Nanobox.BUTTON1));
}
