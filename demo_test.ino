byte lightPins[] = {4, 3, 2, 1, 0, 8, 9, 10};
byte programPin = 5;
int speedPin = A6;

byte program = 0;
short time = 1000;

void setup() {
  for (int i=0; i<8; i++) {
    pinMode(lightPins[i], OUTPUT);
  }  
  pinMode(programPin, INPUT);
}

void loop() {
  readInputs();
  if (program == 1) {
    switchAllLights(1);
    delay(time);
    switchAllLights(0);
    delay(time);
  } else {
    for (byte i = 0; i < 8; i++) {
      digitalWrite(lightPins[i], 1);
      delay(time);
    }
    switchAllLights(0);
  }
}

void switchAllLights(byte value) {
    digitalWrite(lightPins[0], value);
    digitalWrite(lightPins[1], value);
    digitalWrite(lightPins[2], value);
    digitalWrite(lightPins[3], value);
    digitalWrite(lightPins[4], value);
    digitalWrite(lightPins[5], value);
    digitalWrite(lightPins[6], value);
    digitalWrite(lightPins[7], value);
}

void readInputs() {
  time = analogRead(speedPin);
  if (digitalRead(programPin) == 1) {
    program = program + 1;
    if (program == 2) {
      program = 0;
    }
    switchAllLights(0);
  }
}
