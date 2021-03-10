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

// game logic
int difficulty = 0;  //0 = Easy, 1 = Normal, 2 = Hard, 3 = Master
bool playing = false; 

<<<<<<< HEAD
<<<<<<< HEAD
const int sequence_lengths[4] = {5, 7, 10, 15};  // length of sequences
const int interval_lengths[4] = {1000, 750, 500, 250};  // milliseconds
const int max_LEDs[4] = {1, 1, 2, 3};  // how many LEDs can trigger at once
vector<bool> nextLEDs(int max_leds);

long random_nr = 0;
=======
int sequence_lengths[4] = {5, 7, 10, 15};  // length of sequences
int interval_lengths[4] = {1000, 750, 500, 250};  // milliseconds
int max_LEDs[4] = {1, 1, 2, 3};  // how many LEDs can trigger at once
>>>>>>> parent of f1cf01e (Update zimon.ino)
=======
int sequence_lengths[4] = {5, 7, 10, 15};  // length of sequences
int interval_lengths[4] = {1000, 750, 500, 250};  // milliseconds
int max_LEDs[4] = {1, 1, 2, 3};  // how many LEDs can trigger at once
>>>>>>> parent of f1cf01e (Update zimon.ino)


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
  }
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
  // TODO: Starting game
}  
  
// old balance code for reference  
  /*
  // Setup game variables
  // Generate random starting point
  // x_axis and y_axis values range from 0 to 256
  long random_long = random();
  byte x_axis = lowByte(random_long);
  random_long = random_long >> 8; //shift out low Byte
  byte y_axis = lowByte(random_long);
    // set starting score. Score ranges from 0 (loss) to 256 (win)
  int score = 128;
    // Update target LEDs and score LED
  //update_LEDs(x_axis, y_axis, 128);
    
    // Set speed parameter (how far does the target move per step?)
  byte spd = 32;
    // Set time parameter (how frequent is the target updated? in ms)
  int time_par = 2500;

  int total_distance = 0;
  int x_distance = 0;
  int y_distance = 0;
    // Setup moat amount of distance (0 - 256) that the player can be off without losing points
  int moat = 30;
    // TODO: Wait until starting state is approximated before starting the game (while loop)
  
  // Accelerometer variables
  int smoothing_value = 10;
  float accel[3]; //for reading new values
  float accel_x[smoothing_value]; // moving average
  float accel_y[smoothing_value];
  float accel_z[smoothing_value];
  float total_x = 0.0;
  float total_y = 0.0;
  float total_z = 0.0;
  float avg_x = 0.0;
  float avg_y = 0.0;
  float avg_z = 0.0;
  int low_threshold = -50;
  int high_threshold = 50; 

  // Wait for player to get ready
  updateRGB(red_rgb);
  delay(2000);
  updateRGB(yellow_rgb);
  delay(2000);
  updateRGB(green_rgb);
  delay(2000);
  updateRGB(no_rgb);
  // Set RGB-LED to LOW to decouple from game-leds
  for(int index = 0; index < 3; index++){
    pinMode(CHANNELS[index], OUTPUT);
    digitalWrite(CHANNELS[index], LOW);
  }  
  unsigned long counter = millis();
  unsigned long next_scoring;  
  // Charge accelerometer
  int i = 0;
  Serial.println("we are here now"); 
  while (i < smoothing_value){
    if(IMU.accelerationAvailable()) {
      IMU.readAcceleration(accel[0], accel[1], accel[2]);
      accel_x[i] = accel[0];  
      total_x += accel[0];
      accel_y[i] = accel[1];
      total_y += accel[1];
      accel_z[i] = accel[2];
      total_z += accel[2];
      i += 1;
 
    }
    Serial.println("we are here"); 
    Serial.println(i); 
  }
  avg_x = total_x / smoothing_value; 
  avg_y = total_y / smoothing_value; 
  avg_z = total_z / smoothing_value; 
  
  int reading_index = 0;  
  // Start while loop which contains the game
  bool game_over = false;
  while (game_over == false) {
    // Update interface

    if(IMU.accelerationAvailable()) {
      IMU.readAcceleration(accel[0], accel[1], accel[2]);
      /* Debug
      Serial.println("Acc values: ");
      Serial.print(accel[0]);
      Serial.print('\t');
      Serial.print(accel[1]);
      Serial.print('\t');
      Serial.println(accel[2]); *
      // Calculating moving averages
      total_x = total_x + accel[0] - accel_x[reading_index];
      total_y = total_y + accel[1] - accel_y[reading_index];
      total_z = total_z + accel[2] - accel_z[reading_index];
      accel_x[reading_index] = accel[0];
      accel_y[reading_index] = accel[1];
      accel_z[reading_index] = accel[2];
      avg_x = total_x / smoothing_value; 
      avg_y = total_y / smoothing_value; 
      avg_z = total_z / smoothing_value; 
      reading_index = (reading_index + 1) % smoothing_value;
      /* Debug
      Serial.println("Acc values: ");
      Serial.print(avg_x);
      Serial.print('\t');
      Serial.print(avg_y);
      Serial.print('\t');
      Serial.println(avg_z);*
      
      x_distance = map(constrain(round(100*avg_x), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - x_axis;
      y_distance = map(constrain(round(100*avg_y), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - y_axis;
      update_LEDs(x_distance, y_distance, score);
    }
    // Update and score every time_par milliseconds
    next_scoring = millis();
    
    if (next_scoring - counter > time_par) {
      // score points
        // Read Accelerometer (readings range from -1.0 to 1.0g) use only part of it (low to high threshold)
      if(IMU.accelerationAvailable()) {
        IMU.readAcceleration(accel[0], accel[1], accel[2]);
        /*Serial.println("Acc values: ");
        Serial.print(accel[0]);
        Serial.print('\t');
        Serial.print(accel[1]);
        Serial.print('\t');
        Serial.println(accel[2]);*
        // Calculating moving averages
        total_x = total_x + accel[0] - accel_x[reading_index];
        total_y = total_y + accel[1] - accel_y[reading_index];
        total_z = total_z + accel[2] - accel_z[reading_index];
        accel_x[reading_index] = accel[0];
        accel_y[reading_index] = accel[1];
        accel_z[reading_index] = accel[2];
        avg_x = total_x / smoothing_value; 
        avg_y = total_y / smoothing_value; 
        avg_z = total_z / smoothing_value; 
        reading_index = (reading_index + 1) % smoothing_value;
      }
        // Compare to target state and calculate points (Manhattan norm)
      x_distance = map(constrain(round(100*avg_x), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - x_axis;
      y_distance = map(constrain(round(100*avg_y), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - y_axis;
      total_distance = abs(x_distance) + abs(y_distance);
      //debug
      Serial.print("Total distance: ");
      Serial.println(total_distance);
      score = constrain(score + (moat - total_distance), 0, 256);
      //debug
      Serial.print("Score: ");
      Serial.println(score);
      // Update target LEDs and score LED
      update_LEDs(x_distance, y_distance, score);
      // Check win or lose conditions
      if (score == 0){
        Serial.println("YOU LOST!");
        game_over = true;
        for(int index = 0; index < 5; index++){
            pinMode(COLOR_PINS[index], OUTPUT);
        }
        for(int index = 0; index < 3; index++){
          pinMode(CHANNELS[index], OUTPUT);
          analogWrite(CHANNELS[index], LOW);
        }
        break;
      }
      if (score == 256){
        Serial.println("YOU WON!");
        game_over = true; 
        for(int index = 0; index < 5; index++){
            pinMode(COLOR_PINS[index], OUTPUT);
        }
        for(int index = 0; index < 3; index++){
          pinMode(CHANNELS[index], OUTPUT);
          analogWrite(CHANNELS[index], LOW);
        }        
        break;
      }
      // Generate random direction
      int random_direction = random() % 4;
      if (random_direction == 0){
        // Update target state
        // reflective boundary
        x_axis = reflectiveConstrain(x_axis + spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis - spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);
        Serial.print("New y: ");
        Serial.println(y_axis);          
      }
      else if (random_direction == 1){
        x_axis = reflectiveConstrain(x_axis - spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis - spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);  
        Serial.print("New y: ");
        Serial.println(y_axis);
      }
      else if (random_direction == 2){
        x_axis = reflectiveConstrain(x_axis + spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis + spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);  
        Serial.print("New y: ");
        Serial.println(y_axis);
      }
      else if (random_direction == 3){
        x_axis = reflectiveConstrain(x_axis - spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis + spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);  
        Serial.print("New y: ");
        Serial.println(y_axis);
      }
      counter = millis();
    }
  }
>>>>>>> parent of f1cf01e (Update zimon.ino)
}

void update_LEDs(int x, int y, int score){
  // Update x-direction indicators
  int sweet_spot = 15;
  if (x <= -sweet_spot){
    analogWrite(RED, map(x, -128, 0, 0, 1023));
    analogWrite(GREEN, LOW);
  }
  else if (x >= sweet_spot){
    analogWrite(GREEN, map(x, 0, 128, 0, 1023));
    analogWrite(RED, LOW);
  }
  else {
    analogWrite(GREEN, LOW);
    analogWrite(RED, LOW);
  }
  if (y <= -sweet_spot){
    analogWrite(BLUE, map(y, -128, 0, 0, 1023));
    analogWrite(YELLOW, LOW);
  }
  else if (y >= sweet_spot){
    analogWrite(YELLOW, map(y, 0, 128, 0, 1023));
    analogWrite(BLUE, LOW);
  }
  else {
    analogWrite(YELLOW, LOW);
    analogWrite(BLUE, LOW);
  }
  analogWrite(WHITE, map(constrain(score - 128, 0, 128), 0, 256, 0, 256));
}

=======
  // TODO: Starting game
}  
  
// old balance code for reference  
  /*
  // Setup game variables
  // Generate random starting point
  // x_axis and y_axis values range from 0 to 256
  long random_long = random();
  byte x_axis = lowByte(random_long);
  random_long = random_long >> 8; //shift out low Byte
  byte y_axis = lowByte(random_long);
    // set starting score. Score ranges from 0 (loss) to 256 (win)
  int score = 128;
    // Update target LEDs and score LED
  //update_LEDs(x_axis, y_axis, 128);
    
    // Set speed parameter (how far does the target move per step?)
  byte spd = 32;
    // Set time parameter (how frequent is the target updated? in ms)
  int time_par = 2500;

  int total_distance = 0;
  int x_distance = 0;
  int y_distance = 0;
    // Setup moat amount of distance (0 - 256) that the player can be off without losing points
  int moat = 30;
    // TODO: Wait until starting state is approximated before starting the game (while loop)
  
  // Accelerometer variables
  int smoothing_value = 10;
  float accel[3]; //for reading new values
  float accel_x[smoothing_value]; // moving average
  float accel_y[smoothing_value];
  float accel_z[smoothing_value];
  float total_x = 0.0;
  float total_y = 0.0;
  float total_z = 0.0;
  float avg_x = 0.0;
  float avg_y = 0.0;
  float avg_z = 0.0;
  int low_threshold = -50;
  int high_threshold = 50; 

  // Wait for player to get ready
  updateRGB(red_rgb);
  delay(2000);
  updateRGB(yellow_rgb);
  delay(2000);
  updateRGB(green_rgb);
  delay(2000);
  updateRGB(no_rgb);
  // Set RGB-LED to LOW to decouple from game-leds
  for(int index = 0; index < 3; index++){
    pinMode(CHANNELS[index], OUTPUT);
    digitalWrite(CHANNELS[index], LOW);
  }  
  unsigned long counter = millis();
  unsigned long next_scoring;  
  // Charge accelerometer
  int i = 0;
  Serial.println("we are here now"); 
  while (i < smoothing_value){
    if(IMU.accelerationAvailable()) {
      IMU.readAcceleration(accel[0], accel[1], accel[2]);
      accel_x[i] = accel[0];  
      total_x += accel[0];
      accel_y[i] = accel[1];
      total_y += accel[1];
      accel_z[i] = accel[2];
      total_z += accel[2];
      i += 1;
 
    }
    Serial.println("we are here"); 
    Serial.println(i); 
  }
  avg_x = total_x / smoothing_value; 
  avg_y = total_y / smoothing_value; 
  avg_z = total_z / smoothing_value; 
  
  int reading_index = 0;  
  // Start while loop which contains the game
  bool game_over = false;
  while (game_over == false) {
    // Update interface

    if(IMU.accelerationAvailable()) {
      IMU.readAcceleration(accel[0], accel[1], accel[2]);
      /* Debug
      Serial.println("Acc values: ");
      Serial.print(accel[0]);
      Serial.print('\t');
      Serial.print(accel[1]);
      Serial.print('\t');
      Serial.println(accel[2]); *
      // Calculating moving averages
      total_x = total_x + accel[0] - accel_x[reading_index];
      total_y = total_y + accel[1] - accel_y[reading_index];
      total_z = total_z + accel[2] - accel_z[reading_index];
      accel_x[reading_index] = accel[0];
      accel_y[reading_index] = accel[1];
      accel_z[reading_index] = accel[2];
      avg_x = total_x / smoothing_value; 
      avg_y = total_y / smoothing_value; 
      avg_z = total_z / smoothing_value; 
      reading_index = (reading_index + 1) % smoothing_value;
      /* Debug
      Serial.println("Acc values: ");
      Serial.print(avg_x);
      Serial.print('\t');
      Serial.print(avg_y);
      Serial.print('\t');
      Serial.println(avg_z);*
      
      x_distance = map(constrain(round(100*avg_x), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - x_axis;
      y_distance = map(constrain(round(100*avg_y), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - y_axis;
      update_LEDs(x_distance, y_distance, score);
    }
    // Update and score every time_par milliseconds
    next_scoring = millis();
    
    if (next_scoring - counter > time_par) {
      // score points
        // Read Accelerometer (readings range from -1.0 to 1.0g) use only part of it (low to high threshold)
      if(IMU.accelerationAvailable()) {
        IMU.readAcceleration(accel[0], accel[1], accel[2]);
        /*Serial.println("Acc values: ");
        Serial.print(accel[0]);
        Serial.print('\t');
        Serial.print(accel[1]);
        Serial.print('\t');
        Serial.println(accel[2]);*
        // Calculating moving averages
        total_x = total_x + accel[0] - accel_x[reading_index];
        total_y = total_y + accel[1] - accel_y[reading_index];
        total_z = total_z + accel[2] - accel_z[reading_index];
        accel_x[reading_index] = accel[0];
        accel_y[reading_index] = accel[1];
        accel_z[reading_index] = accel[2];
        avg_x = total_x / smoothing_value; 
        avg_y = total_y / smoothing_value; 
        avg_z = total_z / smoothing_value; 
        reading_index = (reading_index + 1) % smoothing_value;
      }
        // Compare to target state and calculate points (Manhattan norm)
      x_distance = map(constrain(round(100*avg_x), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - x_axis;
      y_distance = map(constrain(round(100*avg_y), low_threshold, high_threshold), low_threshold, high_threshold, 0, 256) - y_axis;
      total_distance = abs(x_distance) + abs(y_distance);
      //debug
      Serial.print("Total distance: ");
      Serial.println(total_distance);
      score = constrain(score + (moat - total_distance), 0, 256);
      //debug
      Serial.print("Score: ");
      Serial.println(score);
      // Update target LEDs and score LED
      update_LEDs(x_distance, y_distance, score);
      // Check win or lose conditions
      if (score == 0){
        Serial.println("YOU LOST!");
        game_over = true;
        for(int index = 0; index < 5; index++){
            pinMode(COLOR_PINS[index], OUTPUT);
        }
        for(int index = 0; index < 3; index++){
          pinMode(CHANNELS[index], OUTPUT);
          analogWrite(CHANNELS[index], LOW);
        }
        break;
      }
      if (score == 256){
        Serial.println("YOU WON!");
        game_over = true; 
        for(int index = 0; index < 5; index++){
            pinMode(COLOR_PINS[index], OUTPUT);
        }
        for(int index = 0; index < 3; index++){
          pinMode(CHANNELS[index], OUTPUT);
          analogWrite(CHANNELS[index], LOW);
        }        
        break;
      }
      // Generate random direction
      int random_direction = random() % 4;
      if (random_direction == 0){
        // Update target state
        // reflective boundary
        x_axis = reflectiveConstrain(x_axis + spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis - spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);
        Serial.print("New y: ");
        Serial.println(y_axis);          
      }
      else if (random_direction == 1){
        x_axis = reflectiveConstrain(x_axis - spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis - spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);  
        Serial.print("New y: ");
        Serial.println(y_axis);
      }
      else if (random_direction == 2){
        x_axis = reflectiveConstrain(x_axis + spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis + spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);  
        Serial.print("New y: ");
        Serial.println(y_axis);
      }
      else if (random_direction == 3){
        x_axis = reflectiveConstrain(x_axis - spd, 0, 256);
        y_axis = reflectiveConstrain(y_axis + spd, 0, 256);
        Serial.print("New x: ");
        Serial.println(x_axis);  
        Serial.print("New y: ");
        Serial.println(y_axis);
      }
      counter = millis();
    }
  }
}

void update_LEDs(int x, int y, int score){
  // Update x-direction indicators
  int sweet_spot = 15;
  if (x <= -sweet_spot){
    analogWrite(RED, map(x, -128, 0, 0, 1023));
    analogWrite(GREEN, LOW);
  }
  else if (x >= sweet_spot){
    analogWrite(GREEN, map(x, 0, 128, 0, 1023));
    analogWrite(RED, LOW);
  }
  else {
    analogWrite(GREEN, LOW);
    analogWrite(RED, LOW);
  }
  if (y <= -sweet_spot){
    analogWrite(BLUE, map(y, -128, 0, 0, 1023));
    analogWrite(YELLOW, LOW);
  }
  else if (y >= sweet_spot){
    analogWrite(YELLOW, map(y, 0, 128, 0, 1023));
    analogWrite(BLUE, LOW);
  }
  else {
    analogWrite(YELLOW, LOW);
    analogWrite(BLUE, LOW);
  }
  analogWrite(WHITE, map(constrain(score - 128, 0, 128), 0, 256, 0, 256));
}

>>>>>>> parent of f1cf01e (Update zimon.ino)
int reflectiveConstrain(int input_value, int lower_bound, int upper_bound){
  if (input_value <= upper_bound && input_value >= lower_bound){
    return input_value;
  }
  else if (input_value > upper_bound){
    input_value = 2*upper_bound - input_value;
    return(reflectiveConstrain(input_value, lower_bound, upper_bound));
  }
  else if (input_value < lower_bound){
    input_value = 2*lower_bound - input_value;
    return(reflectiveConstrain(input_value, lower_bound, upper_bound));
  }
  updateRGB(no_rgb);
}

void updateRGB(RGB_Code rgb){
  analogWrite(RED_CHANNEL, map(rgb.r, 0, 255, 0, 1023));
  analogWrite(GREEN_CHANNEL, map(rgb.g, 0, 255, 0, 1023));
  analogWrite(BLUE_CHANNEL, map(rgb.b, 0, 255, 0, 1023));
} */
