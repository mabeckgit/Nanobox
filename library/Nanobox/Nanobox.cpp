/*
 * Nanobox.cpp 
 * Library containing convenience methods for the nanobox
 */
#include "Arduino.h"
#include "Nanobox.h"

// blink LED on given pin for duration in miilliseconds
void blinkLED(int pin, int duration){
	digitalWrite(pin, HIGH); 
	delay(duration); 
	digitalWrite(pin, LOW); 
}
// repeated blinking
void blinkLED(int pin, int duration, int repeats){
	while(repeats)
	{
		blinkLED(pin, duration);
		delay(duration); 
		repeats = repeats - 1; 
	}
}
// repeated blinking with non-equal on-/off-periods
void blinkLED(int pin, int on_duration, int repeats, int off_duration){
	while(repeats)
	{
		blinkLED(pin, on_duration);
		delay(off_duration); 
		repeats = repeats - 1; 
	}
}

