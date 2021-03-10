/*
 * Nanobox.cpp 
 * Library containing convenience methods for the nanobox
 */
#include "Nanobox.h"
#include <algorithm>
#include "Arduino.h"

//Default Constructor
NanoboxClass::NanoboxClass(){
	//Set button pins as pullup-inputs and initialize press time variables
	for(int index = 0; index < 6; index++){
		pinMode(BUTTON_PINS[index], INPUT_PULLUP);
		pressTimes[index] = millis();
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
void NanoboxClass::blinkLED(int pin, int on_duration, 
							int repeats, int off_duration){
	while(repeats)
	{
		blinkLED(pin, on_duration);
		delay(off_duration); 
		repeats = repeats - 1; 
	}
}
// control RGB-LED
void NanoboxClass::updateRGB(RGB_Code rgb){
	analogWrite(RED_CHANNEL, map(rgb.r, 0, 255, 0, max_brightness));
	analogWrite(GREEN_CHANNEL, map(rgb.g, 0, 255, 0, max_brightness));
	analogWrite(BLUE_CHANNEL, map(rgb.b, 0, 255, 0, max_brightness));
}

// Detection of rising or falling edge. Uses internal pull-ups and debouncing
bool NanoboxClass::reactiveButton(int pin, bool rising){
	// get index relating to button pin
	const int* buttonPin;
	buttonPin = std::find(BUTTON_PINS, BUTTON_PINS+6, pin);
	int index = std::distance(BUTTON_PINS, buttonPin);
	// return False if pin does not match any of Nanobox buttons
	if(buttonPin == BUTTON_PINS+6){
		return false;
	}
	else{
		// get previous state
		bool oldState = reactiveStates[index];
		// get time button has been pressed or released
		long time_pressed = switchTime(pin);
		//set reactiveStates variable according to switch 
		if(time_pressed < -debounceTimeRelease){
			reactiveStates[index] = false;
		}
		else if(time_pressed > debounceTimePress){
			reactiveStates[index] = true;
		}
		//detect falling edge/button-release
		if(!rising && oldState && !reactiveStates[index]){
			return true;
		}
		//detect rising edge/button-press
		else if(rising && !oldState && reactiveStates[index]){
			return true;
		}
		else{
			return false;
		}
	}
}

/* return time of a button pressed (or not pressed), doubles as debouncing
 * This function must be added to the loop function of the main-sketch to be 
 * used as timer
 * Implicitly used by Nanobox::reactiveButton
 * Returns positive values indicating the time the button has been pushed or 
 * negative values indicating the time the button has not been pushed.
 */
long NanoboxClass::switchTime(int pin){
	const int* buttonPin;
	buttonPin = std::find(BUTTON_PINS, BUTTON_PINS+6, pin);
	// return 0 if pin does not match any of Nanobox buttons
	if(buttonPin == BUTTON_PINS+6){
		return 0;
	}
	else{
		// get correct variable
		int index = std::distance(BUTTON_PINS, buttonPin);
		long &pressTime = pressTimes[index];
		bool &buttonState = buttonStates[index];
		// reset timer if state has changed
		if(digitalRead(pin) != buttonState){
			buttonState = ! buttonState;
			pressTime = millis();
		}
		// button pushed
		if(buttonState == LOW){
			return millis() - pressTime;
		}
		// button not pushed
		else{
			return pressTime - millis();
		}
	}
}