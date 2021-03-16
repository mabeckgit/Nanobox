/*
 * Example for retrieving the time a button has been pressed
 * or not pressed from the Nanobox class. In the serial 
 * monitor you can read the time in milliseconds since the
 * button has changed state the last time. Positive values
 * indicate that the button had been hold down for that amount
 * of time. Negative values are the time since the button had 
 * been released. 
 */
#include "Nanobox.h"

long st = 0;


void setup() {
	Serial.begin(115200);
}

void loop() {
  st = Nanobox.switchTime(Nanobox.BUTTON2);
  if(st > 0){
    Serial.print("Button pressed for ");
    Serial.print(st);
    Serial.println(" ms.");
  }
  else{
	Serial.print("Button has not been pressed for ");
	Serial.print(-st);
	Serial.println(" ms.");
  }
  //A small delay for keeping the log readable
  delay(100);
}
