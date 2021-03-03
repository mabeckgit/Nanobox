/*
 * Nanobox.h 
 * Library header for Nanobox library
 */
 
 #ifndef NANOBOX_INCLUDED
 #define NANOBOX_INCLUDED
 
 #include "Arduino.h"
 
 class NanoboxClass {
	 public:
		// Constructor
		NanoboxClass();
		/*
		 * Output Logic
		 */
		// constants mapping LED colors to pins
		const int RED = 2; 
		const int BLUE = 3;
		const int YELLOW = 6;
		const int GREEN = 9;
		const int WHITE = 5;
		const int COLOR_PINS[5] = {2, 3, 6, 9, 5};
		// common-cathode LED channels
		const int RED_CHANNEL = A0;
		const int GREEN_CHANNEL = A3;
		const int BLUE_CHANNEL = A2;
		const int RGB_CHANNELS[3] = {A0, A3, A2};
		 
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
		 
		 // Button logic
		 bool reactiveButton(int pin, bool rising = true);
		 long switchTime(int pin);
		 
		 /*
		  * Input Logic
		  */
		 // constants mapping buttons to pins
		const int BUTTON1 = 7;
		const int BUTTON2 = 8;
		const int BUTTON3 = 10;
		const int BUTTON4 = 13;
		const int BUTTON5 = 11;
		const int BUTTON6 = 12;
		const int BUTTON_PINS[6] = {7, 8, 10, 13, 11, 12};
		const int RESET_PIN = A1;

	private:
		// Used for reactiveButton function
		bool reactiveStates[6] = {false, false, false, false, false, false};
		
		// due to internal pull-ups the default state of all button inputs is high. 
		// Used for switchTime function
		bool buttonStates[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
		// long variables giving the last time a button changed state
		long pressTimes[6] = {0, 0, 0, 0, 0, 0};
		long debounceTimePress = 20;
		long debounceTimeRelease = 20;
};

extern NanoboxClass Nanobox;	// The Nanobox object
#endif
