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
vector<vector<bool>> createEasySequence();


void setup() {
  //debugging
  Serial.begin(115200);
  while(!Serial);
  Nanobox.updateRGB(Nanobox.RGB_BLUE);
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
	// TODO: switch-case for easy, normal, hard, master
	vector<vector<bool>> led_sequence = createEasySequence();

	while(true){
	  for(int i=0; i<sequence_lengths[difficulty]; i++){
		for(int j=0; j<4; j++){
		  digitalWrite(Nanobox.COLOR_PINS[j], led_sequence[i][j]);
		}
		delay(interval_lengths[difficulty]);
	  }
	}
	//TODO: receive input and compare to led_sequence
  }
}  
// TODO: Extend to max-LEDs and sequence-length as function input
vector<vector<bool>> createEasySequence(){
  vector<vector<bool>> new_sequence;
  
  long random_nr = 0;
  // We need 2 bits to determine 1 LED in each step of the sequence
  for(int i=0; i < sequence_lengths[0]*2; i = i+2){
	// generate new random number if new bits needed
	if(i % 32 == 0){
	  random_nr = random();
	}
	// Add a red LED to the sequence
	if(bitRead(random_nr, i) && bitRead(random_nr, i+1)){
	  vector<bool> new_vector{true, false, false, false};
	  new_sequence.push_back(new_vector);
	  //new_sequence[0][i/2] = true;
	}
	//Add a blue LED to the sequence
	else if(bitRead(random_nr, i)){
	  vector<bool> new_vector{false, true, false, false};
	  new_sequence.push_back(new_vector);
	  //new_sequence[1][i/2] = true;
	}
	//Add a yellow LED to the sequence
	else if(bitRead(random_nr, i+1)){
	  vector<bool> new_vector{false, false, true, false};
	  new_sequence.push_back(new_vector);
	  //new_sequence[2][i/2] = true; 
	}
	else{
	  vector<bool> new_vector{false, false, false, true};
	  new_sequence.push_back(new_vector);
	  //new_sequence[3][i/2] = true;
	}
  }
  return new_sequence;
}
