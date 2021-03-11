/* Example on how to use the blinkLED function for controlling multiple LEDs
 * at once
 */
 
 #include "Nanobox.h"
 // Vector.h is needed. Install it through the library manager
 #include <Vector.h>


Vector<int> vector;
int storage_array[4];


void setup(){
	vector.setStorage(storage_array);
	vector.push_back(Nanobox.RED);
	vector.push_back(Nanobox.GREEN);
}
 
void loop() {
	Nanobox.blinkLED(vector, 250);
	delay(1000);
}
	 
	 