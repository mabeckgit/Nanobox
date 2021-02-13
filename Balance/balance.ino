#include <Arduino_LSM6DS3.h>

/* Simple balancing game using the IMU and random numbers 
The random number generator determines in which the orientation the nanobox must be brought
LED's indicate the deviation from the orientation needed and the orientation the nanobox currently is in:
Red: tilt to the right needed, Green: tilt to the left needed. Blue: Tilt to the top needed. Yellow: Tilt to 
the bottom needed.
The white LED responds to the points collected. More points equal a brighter LED. 
The game ends and resets when the LED reaches maximal brightness.
If the LED gets too dim the game is lost instead

*/

// Input Logic
const int BUTTON1 = 7;
const int BUTTON2 = 8;
const int BUTTON3 = 10;
const int BUTTON4 = 13;
const int BUTTON5 = 11;
const int BUTTON6 = 12;
const int BUTTON_PINS[6] = {7, 8, 10, 13, 11, 12};
const int RESET_PIN = A1;

//Output Logic
const int RED = 2;
const int BLUE = 3;
const int YELLOW = 6;
const int GREEN = 9;
const int WHITE = 5;
const int COLOR_PINS[5] = {2, 3, 6, 9, 5};
const int PIEZO = 4;
bool button6_state = LOW;
const int NOTES[4] = {262, 294, 330, 349};
const int RED_CHANNEL = A0;
const int GREEN_CHANNEL = A3;
const int BLUE_CHANNEL = A2;
const int CHANNELS[3] = {A0, A3, A2};

//RGB Values
struct RGB_Code {
  int r, g, b;
};

//Standard RGB Values
struct RGB_Code red_rgb = {255, 0, 0};
struct RGB_Code yellow_rgb = {255, 255, 0};
struct RGB_Code green_rgb = {0, 255, 0};
struct RGB_Code white_rgb = {255, 255, 255};
struct RGB_Code no_rgb = {0, 0, 0};

void setup() {
  // Input logic
  for(int index = 0; index < 6; index++){
    pinMode(BUTTON_PINS[index], INPUT);
  }
  pinMode(RESET_PIN, INPUT);

  // Output Logic
  for(int index = 0; index < 5; index++){
    pinMode(COLOR_PINS[index], OUTPUT);
  }
  for(int index = 0; index < 3; index++){
    pinMode(CHANNELS[index], OUTPUT);
    analogWrite(CHANNELS[index], LOW);
  }
  pinMode(PIEZO, OUTPUT);
  
  Serial.begin(115200);
  while(!Serial);
  
  // Setup IMU
  if (!IMU.begin()){
    Serial.println("Failed to initialize IMU!");
    while(1);
  }
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz"); 
  Serial.println();
}

// TODO: MORE REACTIVE INTERFACE

void loop() {
  // debug
  updateRGB(white_rgb);
  delay(200);
  updateRGB(no_rgb);
  delay(200);
  updateRGB(white_rgb);
  delay(200);
  updateRGB(no_rgb);
  delay(200);  
  updateRGB(white_rgb);
  delay(200);
  updateRGB(no_rgb);
  delay(200);
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
      Serial.println(accel[2]); */
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
      Serial.println(avg_z);*/
      
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
        Serial.println(accel[2]);*/
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
}
