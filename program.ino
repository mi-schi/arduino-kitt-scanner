int lightPins[] = {3, 4, 5, 6, 7, 8, 9, 10};
int programPin = 2;
int speedPin = A0;

int msMin = 50;
int msMax = 500;
int program = 0;
unsigned long programSwitchTime = 0;
int programSwitchDelay = 500;

void setup() {
  //Serial.begin(9600);
  //Serial.println(lightPins[led]);
  
  for (int i=0; i<8; i++) {
    pinMode(lightPins[i], OUTPUT);
  }  
  pinMode(programPin, INPUT_PULLUP);

  // start animation
  switchLights("01234567", HIGH);
  delay(1000);
  switchLights("01234567", LOW);
  delay(300);
}

void loop() {
  if (program == 1) {
    police();
  } else if (program == 2) {
    outToIn();
  } else if (program == 3) {
    flasher();
  } else if (program == 4) {
    leftToRight();
  } else if (program == 5) {
    inToOut();
  } else {
    kitt();
  }
}

void police() {
  msMin = 50;
  msMax = 300;
  String sequences[] = {"0123", "4567"};

  for (int i=0; i<2; i++) {
    switchLights(sequences[i], HIGH);
    sensoredDelay(1);
    switchLights(sequences[i], LOW);
    sensoredDelay(1);
    switchLights(sequences[i], HIGH);
    sensoredDelay(1);
    switchLights(sequences[i], LOW);
    
    sensoredDelay(1.5);
  }
}

void outToIn() {
  String sequences[] = {"07", "16", "25", "34"};
  sequence(sequences);
}

void flasher() {
  msMin = 50;
  msMax = 500;
  switchLights("01234567", HIGH);
  sensoredDelay(1);
  switchLights("01234567", LOW);
  sensoredDelay(1);
}

void leftToRight() {
  String sequences[] = {"04", "15", "26", "37"};
  sequence(sequences);
}

void inToOut() {
  msMin = 50;
  msMax = 400;
  String sequences[] = {"34", "25", "16", "07"};
  for (int i=0; i<4; i++) {  
    switchLights(sequences[i], HIGH);
    sensoredDelay(1);
  }
  switchLights("01234567", LOW);
  sensoredDelay(2);
}

void sequence(String sequences[]) {
  msMin = 50;
  msMax = 400;
  for (int i=0; i<3; i++) {
    switchLights(sequences[i], HIGH);
    sensoredDelay(1);
    switchLights(sequences[i], LOW);
  } 
  for (int i=3; i>0; i--) {
    switchLights(sequences[i], HIGH);
    sensoredDelay(1);
    switchLights(sequences[i], LOW);
  }
}

void kitt() {
  msMin = 5;
  msMax = 100;
  for (int i=0; i<7; i++) {
    digitalWrite(lightPins[i], HIGH);
    sensoredDelay(1);
    digitalWrite(lightPins[i+1], HIGH);
    sensoredDelay(1);
    digitalWrite(lightPins[i], LOW);
    sensoredDelay(2);
  }
  for (int i=7; i>0; i--) {
    digitalWrite(lightPins[i], HIGH);
    sensoredDelay(1);
    digitalWrite(lightPins[i-1], HIGH);
    sensoredDelay(1);
    digitalWrite(lightPins[i], LOW);
    sensoredDelay(2);
  }
}

void switchLights(String leds, boolean value) {
  for (int i=0; i<leds.length(); i++) {
    int led = leds[i] - '0';
    digitalWrite(lightPins[led], value);
  }
}

void sensoredDelay(int factor) {
  unsigned long startTime = millis();
  int time = 50 * factor;
  while (millis() - startTime < time) {
    time = map(analogRead(speedPin), 0, 1023, msMin, msMax) * factor;
    if (millis() - programSwitchTime > programSwitchDelay && digitalRead(programPin) == LOW) {
      program = program + 1;
      if (program == 6) {
        program = 0;
      }
      switchLights("01234567", LOW);
      programSwitchTime = millis();
    }
  }
}
