/*
 * Nanobox.h 
 * Library header for Nanobox library
 */
 
 #include "Arduino.h"
 
 // constants mapping LED colors to pins
const int RED = 2; 
const int BLUE = 3;
const int YELLOW = 6;
const int GREEN = 9;
const int WHITE = 5;
// common-cathode LED channels
const int RED_CHANNEL = A0;
const int GREEN_CHANNEL = A3;
const int BLUE_CHANNEL = A2;
 
 // constants defining 3-byte RGB-values
 struct RGB_Code {
	 int r, g, b;
 };
const struct RGB_Code RGB_RED = {255, 0, 0};
const struct RGB_Code RGB_GREEN = {0, 255, 0};
const struct RGB_Code RGB_BLUE = {0, 0, 255};
const struct RGB_Code RGB_YELLOW = {255, 255, 0};
const struct RGB_Code RGB_MAGENTA = {255, 0, 255};
const struct RGB_Code RGB_CYAN = {0, 255, 255};
const struct RGB_Code RGB_WHITE = {255, 255, 255};
const struct RGB_Code RGB_BLACK = {0, 0, 0};
 
 // Overloaded blink functions
 void blinkLED(int pin, int duration);
 void blinkLED(int pin, int duration, int repeats);
 void blinkLED(int pin, int on_duration, int repeats, int off_duration);
 
 // Rising and falling edges