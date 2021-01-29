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
//Start with Yellow
struct RGB_Code rgb = {255, 255, 0};
int zero_value = 2;

// TODO: Mapping between color-words and RGB_Codes

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
  // TODO: Setup RTC and ICM
  // TODO: Setup Serial for debugging and testing
  Serial.begin(115200);
  // TODO: Write functions for rising and falling edges
  // TODO: Implement reset-button to reset Arduino

}

void loop() {
  // put your main code here, to run repeatedly:
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
