/* 
 * Example to use RGB-LED and the RGB_Codes packaged with the Nanobox
 * Press any of the 6 main buttons to change the RGB_Codes used in the LED
 * Button 1 -> Red
 * Button 2 -> Green
 * Button 3 -> White
 * Button 4 -> Cyan
 * Button 5 -> "Black"
 * Button 6 -> Custom
 *
 * You can also replace the above colors by these unused codes: magenta, blue,
 * yellow.
 * Or come up with your own by adjusting the custom-code in below's code.
 * 
 */

#include "Nanobox.h"

const struct NanoboxClass::RGB_Code custom_code = {255, 165, 0};  //orange 

void setup(){
}

void loop() {
	// read button pressed
	int button_pressed = Nanobox.buttonPressed();
	switch(button_pressed){
		case 7:
			Nanobox.updateRGB(Nanobox.RGB_RED);
			break;
		case 8:
			Nanobox.updateRGB(Nanobox.RGB_GREEN);
			break;
		case 10:
			Nanobox.updateRGB(Nanobox.RGB_WHITE);
			break;
		case 13:
			Nanobox.updateRGB(Nanobox.RGB_CYAN);
			break;
		case 11:
			Nanobox.updateRGB(Nanobox.RGB_BLACK);
			break;
		case 12:
			Nanobox.updateRGB(custom_code);
			break;
		default:
			break;
	}
}