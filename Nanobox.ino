// Input Logic
const int BUTTON1 = 7;
const int BUTTON2 = 8;
const int BUTTON3 = 1;
const int BUTTON4 = 13;
const int BUTTON5 = 2;
const int BUTTON6 = 12;
const int BUTTON_PINS[6] = {7, 8, 1, 13, 2, 12};
const int RESET_PIN = 10;

//Output Logic
const int RED = 2;
const int BLUE = 3;
const int YELLOW = 6;
const int GREEN = 9;
const int COLOR_PINS[4] = {2, 3, 6, 9};
const int PIEZO = 4;
const int RED_CHANNEL = A3;
const int GREEN_CHANNEL = A6;
const int BLUE_CHANNEL = A7;
const int CHANNELS[3] = {A3, A6, A7};

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
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int index = 0; index < 4; index++){
    digitalWrite(COLOR_PINS[index], digitalRead(BUTTON_PINS[index]));
    if (digitalRead(BUTTON_PINS[index]) == HIGH){
      Serial.println("Button pressed: ");
      Serial.print(BUTTON_PINS[index]);
    }
  }
}
