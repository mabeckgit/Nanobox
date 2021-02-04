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
const int RED_CHANNEL = A3;
const int GREEN_CHANNEL = A6;
const int BLUE_CHANNEL = A7;
const int CHANNELS[3] = {A3, A6, A7};

//RGB Values
struct RGB_Code {
  int r, g, b;
};

void setup() {
  // Input logic
  for(int index = 0; index < 6; index++){
    pinMode(BUTTON_PINS[index], INPUT);
  }
  pinMode(RESET_PIN, INPUT);

  // Output Logic
  for(int index = 0; index < 4; index++){
    pinMode(COLOR_PINS[index], OUTPUT);
  }
  for(int index = 0; index < 3; index++){
    pinMode(CHANNELS[index], OUTPUT);
  }
  pinMode(PIEZO, OUTPUT);
  
  // TODO: Setup Serial for debugging and testing
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
  // TODO: Write functions for rising and falling edges
  // TODO: Implement reset-button to reset Arduino
  // TODO: Setup RTC and ICM
}

void loop() {
  // Setup game variables
    // Generate random starting point
    // Update target LEDs
    // Update score LED
    // Set speed parameter (how far does the target move per step?)
    // Set time parameter (how frequent is the target updated?)
    // Setup score factor (what is the relationship between distance to target and scoring?)
    // Wait until starting state is approximated before starting the game (while loop)
  // Start while loop which contains the game
  bool game_over = false;
  while (game_over == false){
    // Generate random direction
    // Update target state
    // Update target LEDs
    // Read Accelerometer  
    // Compare to target state and calculate points
    // Update score LED
    // Check win or lose conditions
    
  }
  
  //Accelerometer variables
  float accel[3];
  if(IMU.accelerationAvailable()) {
    IMU.readAcceleration(accel[0], accel[1], accel[2]);
    Serial.println("Acc values: ");
    Serial.print(accel[0]);
    Serial.print('\t');
    Serial.print(accel[1]);
    Serial.print('\t');
    Serial.println(accel[2]);
    for(int index = 0; index < 3; index++){
      analogWrite(COLOR_PINS[index], map(constrain(round(100*accel[index]), 0, 100), 0, 100, 0, 1023));
    }
  }

  float a, b, c;
  if (IMU.gyroscopeAvailable()) {
    /*IMU.readGyroscope(a, b, c);
    Serial.println("Gyrovalues: ");
    Serial.print(a);
    Serial.print('\t');
    Serial.print(b);
    Serial.print('\t');
    Serial.println(c);*/
  }

  for(int index = 0; index < 5; index++){
    digitalWrite(COLOR_PINS[index], digitalRead(BUTTON_PINS[index]));
  }
  //Rising Edge
  if (digitalRead(BUTTON6) == HIGH && button6_state == LOW){
    tone(PIEZO, NOTES[0], 250);
    cycleRGB();
    updateRGB(rgb);
  }
  //Falling Edge
  else if (digitalRead(BUTTON6) == LOW && button6_state == HIGH){
    noTone(PIEZO);
  }
  button6_state = digitalRead(BUTTON6);
  delay(500);
}

RGB_Code cycleRGB() {
  zero_value = (zero_value + 1) % 3;
  rgb = {255, 255, 255};
  // Cyan
  if (zero_value == 0){
    rgb.r = 0;
  }
  // Purple
  if (zero_value == 1){
    rgb.g = 0;
  }
  // Yellow
  if (zero_value == 2){
    rgb.b = 0;
  }
}

void updateRGB(RGB_Code rgb){
  analogWrite(A3, map(rgb.r, 0, 255, 0, 1023));
  analogWrite(A6, map(rgb.g, 0, 255, 0, 1023));
  analogWrite(A7, map(rgb.b, 0, 255, 0, 1023));
}
