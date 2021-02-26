/*
 * Nanobox.cpp 
 * Library containing convenience methods for the nanobox
 */
#include "Nanobox.h"
#include <algorithm>
#include "Arduino.h"

//Default Constructor
NanoboxClass::NanoboxClass(){
	//Set button pins as pullup-inputs
	for(int index = 0; index < 6; index++){
		pinMode(BUTTON_PINS[index], INPUT_PULLUP);
	}
	//Set LED pins as outputs
	for(int index = 0; index < 5; index++){
		pinMode(COLOR_PINS[index], OUTPUT);
	}
	for(int index = 0; index < 3; index++){
		pinMode(RGB_CHANNELS[index], OUTPUT);
		analogWrite(RGB_CHANNELS[index], LOW);
	}
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
// Setup detection of rising or falling edge in Button. Uses internal pull-ups 
// and debouncing
// TODO: Debouncing
bool NanoboxClass::reactiveButton(int pin, bool rising){
	const int* buttonPin;
	buttonPin = std::find(BUTTON_PINS, BUTTON_PINS+6, pin);
	// return False if pin does not match any of Nanobox buttons
	if(buttonPin == BUTTON_PINS+6){
		//return false;
	}
	else{
		int index = std::distance(BUTTON_PINS, buttonPin);
		bool &buttonState = ButtonStates[index];
		bool new_state = digitalRead(pin);
		//detect falling edge (due to Pull-up we have to invert the signal)
		if(!rising && buttonState && new_state){
			buttonState = new_state;
			return true;
		}
		//detect rising edge
		else if(rising && buttonState&& !new_state){
			buttonState = new_state;
			return true;
		}
		else{
			buttonState = new_state;
			return false;
		}

	}
}

NanoboxClass Nanobox;	// Create a Nanobox object
