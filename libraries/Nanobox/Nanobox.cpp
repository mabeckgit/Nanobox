/*
 * Nanobox.cpp 
 * Library containing convenience methods for the nanobox
 */
#include "Nanobox.h"

//Default Constructor
NanoboxClass::NanoboxClass(){
}

// blink LED on given pin for duration in miilliseconds
void NanoboxClass::blinkLED(int pin, int duration){
	digitalWrite(pin, HIGH); 
	delay(duration); 
	digitalWrite(pin, LOW); 
}
// repeated blinking
void NanoboxClass::blinkLED(int pin, int duration, int repeats){
	while(repeats)
	{
		blinkLED(pin, duration);
		delay(duration); 
		repeats = repeats - 1; 
	}
}
// repeated blinking with non-equal on-/off-periods
void NanoboxClass::blinkLED(int pin, int on_duration, int repeats, int off_duration){
	while(repeats)
	{
		blinkLED(pin, on_duration);
		delay(off_duration); 
		repeats = repeats - 1; 
	}
}

NanoboxClass Nanobox;	// Create a Nanobox object
