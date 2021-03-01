/*
 * Example for edge detection. The RED-LED will change state 
 * with a press of BUTTON1 and remain in that state until the
 * button is pressed again. In contrast the YELLOW-LED will
 * be on only while the button is pressed
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
