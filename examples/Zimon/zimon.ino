/* Simple memory game using random numbers 
The random number generator determines which LED-button pair will be added to 
the sequence. 
The white LED serves as signal for the player to repeat the sequence seen
The game ends and resets when a maximum length is correctly remembered, a 
mistake was made or when the player does not respond within a given window.
Button 5 is used to change difficulty (only when game is stopped)
Button 6 is used to stop/start the game
*/
#include <Arduino_LSM6DS3.h>
#include "Nanobox.h"
#include <vector>
using std::vector;

// game logic
int difficulty = 0;  //0 = Easy, 1 = Normal, 2 = Hard, 3 = Master
bool playing = false; 

const int sequence_lengths[4] = {5, 7, 10, 15};  // length of sequences
const int interval_lengths[4] = {1000, 750, 500, 250};  // milliseconds
const int max_LEDs[4] = {1, 1, 2, 3};  // how many LEDs can trigger at once
vector<bool> nextLEDs(int max_leds);

long random_nr = 0;


void setup() {
  Nanobox.updateRGB(Nanobox.RGB_BLUE);
  randomSeed(analogRead(A0));
}


void loop() {
  // Select difficulty and wait for game-start
  while(!playing){
	if(Nanobox.reactiveButton(Nanobox.BUTTON5)){
	  difficulty = (difficulty + 1) % 4;
	  switch(difficulty){
		case 0:
		  Nanobox.updateRGB(Nanobox.RGB_BLUE);
		  break;
		case 1:
		  Nanobox.updateRGB(Nanobox.RGB_GREEN);
		  break;
		case 2:
		  Nanobox.updateRGB(Nanobox.RGB_YELLOW);
		  break;
		case 3:
		  Nanobox.updateRGB(Nanobox.RGB_RED);
		  break;
		default:
		  break;
	  }
	}
	if(Nanobox.reactiveButton(Nanobox.BUTTON6)){
	  playing = true; 
	}
  }
  while(playing){
	// Create sequences
	vector<vector<bool>> led_sequence{}; 

	while(true){
	  for(int i=0; i<sequence_lengths[difficulty]; i++){
		led_sequence.push_back(nextLEDs(max_LEDs[difficulty]));
		for(int j=0; j<4; j++){
		  if(led_sequence[i][j]){
			Nanobox.blinkLED(Nanobox.COLOR_PINS[j], 250);
		  }
		}
		delay(interval_lengths[difficulty]);
	  }
	}
	//TODO: receive input and compare to led_sequence
  }
}  

// TODO: On master-difficulty have 1, 2, or 3 LEDs instead of always 3
vector<bool> nextLEDs(int max_leds){
  vector<bool> new_vector; 

  // Need 2 bits to determine which LEDs trigger in each step of the sequence
  random_nr = random();
  int return_leds = max_leds;
  //determine number of LEDs to return
  if(max_leds == 3){
	return_leds = 1 + (random_nr % 3);
	random_nr = random();
  }
  
  switch(random_nr % 4){
	case 0:
	  if(max_leds == 1){
	    new_vector = {true, false, false, false};
	  }
	  else if(max_leds == 2){
		new_vector = {true, false, true, false};
	  }
	  else{
		new_vector = {false, true, true, true};
	  }
	  break;
	case 1:
	  if(max_leds == 1){
	    new_vector = {false, true, false, false};
	  }
	  else if(max_leds == 2){
		new_vector = {true, false, false, true};
	  }
	  else{
		new_vector = {true, false, true, true};
	  }
	  break;
	case 2:
	  if(max_leds == 1){
	    new_vector = {false, false, true, false};
	  }
	  else if(max_leds == 2){
		new_vector = {false, true, true, false};
	  }
	  else{
		new_vector = {true, true, false, true};
	  }
	  break;
	case 3:
	  if(max_leds == 1){
		new_vector = {false, false, false, true};
	  }
	  else if(max_leds == 2){
		new_vector = {false, true, false, true};
	  }
	  else{
		new_vector = {true, true, true, false};
	  }
	  break;
  }
  return new_vector;
}
