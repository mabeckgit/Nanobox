/*
 * Nanobox.cpp 
 * Library containing convenience methods for the nanobox
 */
#include "Nanobox.h"
#include <algorithm>
#include "Arduino.h"
// Arduino-specific library simulating std::vector
#include <Vector.h>


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

// repeated blinking with non-equal on-/off-periods
void NanoboxClass::blinkLED(int pin, int duration, 
							int repeats, int off_duration){
	while(repeats > 1)
	{
		digitalWrite(pin, HIGH);
		delay(duration);
		digitalWrite(pin, LOW);
		if(off_duration != 0){
		  delay(off_duration); 
		}
		else{
		  delay(duration);
		}
		repeats = repeats - 1; 
	}
	digitalWrite(pin, HIGH);
	delay(duration);
	digitalWrite(pin, LOW);
}
// repeated blinking of several LEDs at once
void NanoboxClass::blinkLED(Vector<int> pins, int duration, 
							int repeats, int off_duration){
	while(repeats > 1)
	{
		for(int i=0; i < pins.size(); i++){
			digitalWrite(pins[i], HIGH);
		}
		delay(duration);
		for(int i=0; i < pins.size(); i++){
			digitalWrite(pins[i], LOW);
		}
		if(off_duration != 0){
			delay(off_duration);
		}
		else{
			delay(duration);
		}
		repeats = repeats - 1;
	}
	for(int i=0; i < pins.size(); i++){
		digitalWrite(pins[i], HIGH);
	}
	delay(duration);
	for(int i=0; i < pins.size(); i++){
		digitalWrite(pins[i], LOW);
	}
}
			

// control RGB-LED
void NanoboxClass::updateRGB(RGB_Code rgb){
	analogWrite(RED_CHANNEL, map(rgb.r, 0, 255, 0, max_brightness));
	analogWrite(GREEN_CHANNEL, map(rgb.g, 0, 255, 0, max_brightness));
	analogWrite(BLUE_CHANNEL, map(rgb.b, 0, 255, 0, max_brightness));
}


// Function that wraps reactiveButton into readout of any button
int NanoboxClass::buttonPressed(bool rising){
	int output = 0;
	for(int i=0; i<(sizeof(BUTTON_PINS)/sizeof(BUTTON_PINS[0])); i++){
		if(reactiveButton(BUTTON_PINS[i], rising)){
			output = BUTTON_PINS[i];
		}
	}
	return output;
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

NanoboxClass Nanobox;  // Create a Nanobox object