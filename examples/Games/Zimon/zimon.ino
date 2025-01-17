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
#include <Vector.h>

// game logic
int difficulty = 0;  //0 = Easy, 1 = Normal, 2 = Hard, 3 = Master
bool playing = false; 

const int sequence_lengths[4] = {5, 7, 10, 15};  // length of sequences
const int MAX_LENGTH = 15;
const int interval_lengths[4] = {1500, 1200, 900, 600};  // milliseconds
const int max_LEDs[4] = {1, 1, 2, 3};  // how many LEDs can trigger at once
Vector<int> nextLEDs(int max_leds);
Vector<int> getInputSequence(int length, int timeout);

long random_nr = 0;

// LEDs to signal game loss
Vector<int> loseVector;
int loseVector_storage[4];

// Button Settings. Change this to your comfort and your own Nanobox
constexpr int red_button = NanoboxClass::BUTTON3;
constexpr int blue_button = NanoboxClass::BUTTON5;
constexpr int yellow_button = NanoboxClass::BUTTON6;
constexpr int green_button = NanoboxClass::BUTTON4;
constexpr int start_button = NanoboxClass::BUTTON2;
constexpr int level_select_button = NanoboxClass::BUTTON1;


void setup() {
  Nanobox.updateRGB(Nanobox.RGB_BLUE);
  randomSeed(analogRead(A0));
  
  loseVector.setStorage(loseVector_storage);
  for(int i=0; i<4; i++){
	loseVector.push_back(Nanobox.COLOR_PINS[i]);
  }
  
  //debug
  Serial.begin(115200);
}


void loop() {
  // Select difficulty and wait for game-start
  while(!playing){
	if(Nanobox.reactiveButton(level_select_button)){
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
	if(Nanobox.reactiveButton(start_button)){
	  playing = true; 
	}
  }
  while(playing){
	// Create sequences
	Vector<Vector<int>> led_sequence;
	Vector<int> led_sequence_storage[MAX_LENGTH];
	led_sequence.setStorage(led_sequence_storage);
	Serial.println("led_sequence initialized"); 
	int current_seq_length = 0;
    for(int i=0; i<sequence_lengths[difficulty]; i++){
	  // Add one more LED-vector to the sequence
  	  led_sequence.push_back(nextLEDs(max_LEDs[difficulty]));
	  current_seq_length++;
	  Serial.print("pushed 1 vector. We are in iteration:");
      Serial.println(current_seq_length);
  	  Nanobox.blinkLED(led_sequence[i], interval_lengths[difficulty]);
	  
	  // wait for and receive input break loop if there is too long a delay
	  // Create input sequence
	  Vector<Vector<int>> input_sequence;
	  Vector<int> input_seq_storage[MAX_LENGTH];
	  input_sequence.setStorage(input_seq_storage);
	  Serial.println("input vector initialized");
	  bool timed_out = false;
	  for(int j=0; j<current_seq_length; j++){
		  // read input
		  Serial.print("Reading input vector: ");
		  Serial.println(j); 
		  Vector<int> new_input = getInputSequence(led_sequence[j].size(),
				interval_lengths[difficulty]*3);
		  // check if timed out
		  if(new_input.size() == 0){
			  Serial.println("Timed out!"); 
			  timed_out = true;
			  break;
		  }
		  else{
			Serial.println("pushing input vector"); 
			input_sequence.push_back(new_input);
		  }
	  }
	  
	  // compare each input to the sequence break loop if wrong
	  // check input sequence
	  Serial.println("comparing sequences");
	  bool matching = true;
	  for(int j=0; j<current_seq_length; j++){
		if(matching && led_sequence[j].size() != input_sequence[j].size()){
			Serial.print("Length mismatch in input: ");
			Serial.println(j); 
			matching = false;
			break;
		}
		else{
			for(int k=0; k<led_sequence[j].size(); k++){
				if(led_sequence[j][k] != input_sequence[j][k]){
					Serial.print("mismatch in vector: ");
					Serial.print(j);
					Serial.print(". At position: ");
					Serial.println(k);
					matching = false;
					break;
				}
			}
		}
		if(!matching){
			break;
		}
	  }
	  if(!matching){
		Serial.println("You lost!"); 
		playing = false;
		// Indicate lost game by LEDs
		Nanobox.blinkLED(loseVector, 100, 5);
		break;
	  }
	  //input was correct
	  Serial.println("Correct, moving on..."); 
	  if(current_seq_length == sequence_lengths[difficulty]){
		  //signal win
		  for(int j=0; j<16; j++){
			  Nanobox.blinkLED(Nanobox.COLOR_PINS[j%5], 200);
		  }
		  playing = false;
	  }
	}
  }
}  


Vector<int> nextLEDs(int max_leds){
  Vector<int> new_vector; 
  static int new_vector_storage[4];
  new_vector.setStorage(new_vector_storage);

  random_nr = random();
  int return_leds = max_leds;
  //determine number of LEDs to return
  if(max_leds == 3){
	return_leds = 1 + (random_nr % 3);
	random_nr = random();
  }
  
  switch(random_nr % 4){
	case 0:
	  if(return_leds == 1){
	    new_vector.push_back(Nanobox.RED);
	  }
	  else if(return_leds == 2){
		new_vector.push_back(Nanobox.RED);
		new_vector.push_back(Nanobox.YELLOW);
	  }
	  else{
		new_vector.push_back(Nanobox.BLUE);
		new_vector.push_back(Nanobox.YELLOW);
		new_vector.push_back(Nanobox.GREEN);
	  }
	  break;
	case 1:
	  if(return_leds == 1){
		new_vector.push_back(Nanobox.BLUE);
	  }
	  else if(return_leds == 2){
		new_vector.push_back(Nanobox.RED);
		new_vector.push_back(Nanobox.GREEN);
	  }
	  else{
		new_vector.push_back(Nanobox.RED);
		new_vector.push_back(Nanobox.YELLOW);
		new_vector.push_back(Nanobox.GREEN);
	  }
	  break;
	case 2:
	  if(return_leds == 1){
		new_vector.push_back(Nanobox.YELLOW);
	  }
	  else if(return_leds == 2){
		new_vector.push_back(Nanobox.BLUE);
		new_vector.push_back(Nanobox.YELLOW);
	  }
	  else{
		new_vector.push_back(Nanobox.RED);
		new_vector.push_back(Nanobox.BLUE);
		new_vector.push_back(Nanobox.GREEN);
	  }
	  break;
	case 3:
	  if(return_leds == 1){
		new_vector.push_back(Nanobox.GREEN);
	  }
	  else if(return_leds == 2){
		new_vector.push_back(Nanobox.BLUE);
		new_vector.push_back(Nanobox.GREEN);
	  }
	  else{
		new_vector.push_back(Nanobox.RED);
		new_vector.push_back(Nanobox.BLUE);
		new_vector.push_back(Nanobox.YELLOW);
	  }
	  break;
  }
  return new_vector;
}

// getInputSequence. Receive them, order them, stop listening
Vector<int> getInputSequence(int length, int timeout){
	Vector<int> readout;
	static int readout_storage[4];
	readout.setStorage(readout_storage);
	
	long start_time = millis();
	//get buttons
	for(int i = 0; i<length; i++){
		int button_read = 0;
		while(millis() - start_time < timeout){
		  button_read = Nanobox.buttonPressed();
		  int led_read = 0;
		  if(button_read != 0){
			//convert to LED-Pins
			switch(button_read){
			  case red_button:
				led_read = Nanobox.RED;
				break;
			  case yellow_button:
				led_read = Nanobox.YELLOW;
				break;
			  case blue_button:
				led_read = Nanobox.BLUE;
				break; 
			  case green_button:
				led_read = Nanobox.GREEN;
				break;
			  default:
				led_read = 0;
				break;
			}
			readout.push_back(led_read);
			// TODO: Adjust brightness per LED
			analogWrite(led_read, 50); 
			start_time = millis();
			break;
		  }
		}
	}
	//bubble sort readout
	for(int i = 0; i<readout.size(); i++){
		if(i+1 < readout.size()){
			if(readout[i] > readout[i+1]){
				int cache = readout[i+1];
				readout[i+1] = readout[i];
				readout[i] = cache; 
			}
		}
	}
	// debug:
	for(int i=0; i<readout.size(); i++){
	  Serial.print("Input signal ");
	  Serial.print(i);
	  Serial.print(" : ");
	  Serial.println(readout[i]);
	}
	// reset LEDs
	delay(250);
	for(int j = 0; j<5; j++){
	  analogWrite(Nanobox.COLOR_PINS[j], LOW);
	}
	delay(250);
	return readout;
}