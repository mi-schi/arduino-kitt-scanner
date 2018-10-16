int lightPins[] = {3, 4, 5, 6, 7, 8, 9, 10};
int programPin = 2;
int speedPin = A0;

int program = 0;
int msMinPerProgram[] = {  5,  50,  50,  60,  50,  50,  40,  30,  15,  15,  40,  40,  30,  30,   5};
int msMaxPerProgram[] = {100, 300, 400, 600, 500, 400, 500, 300, 400, 400, 400, 400, 400, 400, 100};
unsigned long programSwitchTime = 0;
int programSwitchDelay = 500;

void setup() {
  // Serial.begin(9600);
  // Serial.println();
  for (int i=0; i<8; i++) {
    pinMode(lightPins[i], OUTPUT);
  }  
  pinMode(programPin, INPUT);
  switchLights("01234567", HIGH);
  delay(1000);
  switchLights("01234567", LOW);
  delay(300);
}

void loop() {
  if (program == 1) {
    // police 2 times
    String sequences[] = {"0123", "4567"};
    for (int i=0; i<2; i++) {
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
      switchLights(sequences[i], LOW);
      if (sensoredDelay(1)) return;
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
      switchLights(sequences[i], LOW);
      
      if (sensoredDelay(1.5)) return;
    }
  } else if (program == 2) {
    // out to in splitted
    String sequences[] = {"07", "16", "25", "34"};
    for (int i=0; i<3; i++) {
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
      switchLights(sequences[i], LOW);
    } 
    for (int i=3; i>0; i--) {
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
      switchLights(sequences[i], LOW);
    }
  } else if (program == 3) {
    // flasher
    switchLights("01234567", HIGH);
    if (sensoredDelay(1)) return;
    switchLights("01234567", LOW);
    if (sensoredDelay(1)) return;
  } else if (program == 4) {
    // left to right splitted
    String sequences[] = {"04", "15", "26", "37"};
    for (int i=0; i<3; i++) {
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
      switchLights(sequences[i], LOW);
    } 
    for (int i=3; i>0; i--) {
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
      switchLights(sequences[i], LOW);
    }
  } else if (program == 5) {
    // in to out splitted
    String sequences[] = {"34", "25", "16", "07"};
    for (int i=0; i<4; i++) {  
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
    }
    switchLights("01234567", LOW);
    if (sensoredDelay(2)) return;
  } else if (program == 6) {
    // police
    switchLights("4567", LOW);
    switchLights("0123", HIGH);
    if (sensoredDelay(2)) return;
    switchLights("0123", LOW);
    switchLights("4567", HIGH);
    if (sensoredDelay(2)) return;
  } else if (program == 7) {
    // flasher 2 times
    switchLights("01234567", HIGH);
    if (sensoredDelay(2)) return;
    switchLights("01234567", LOW);
    if (sensoredDelay(1)) return;
    switchLights("01234567", HIGH);
    if (sensoredDelay(2)) return;
    switchLights("01234567", LOW);
    if (sensoredDelay(4)) return;  
  } else if (program == 8) {
    // snake
    for (int i=0; i<=7; i++) {
      digitalWrite(lightPins[i], HIGH);
      if (sensoredDelay(1)) return;
    }
    for (int i=0; i<=7; i++) {
      digitalWrite(lightPins[i], LOW);
      if (sensoredDelay(1)) return;
    }
  } else if (program == 9) {
    // snake reverse
    for (int i=7; i>=0; i--) {
      digitalWrite(lightPins[i], HIGH);
      if (sensoredDelay(1)) return;
    }
    for (int i=7; i>=0; i--) {
      digitalWrite(lightPins[i], LOW);
      if (sensoredDelay(1)) return;
    }
  } else if (program == 10) {
    // out to in full
    String sequences[] = {"07", "16", "25", "34"};
    for (int i=0; i<4; i++) {
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
    }
    for (int i=0; i<4; i++) {
      switchLights(sequences[i], LOW);
      if (sensoredDelay(1)) return;
    }
  } else if (program == 11) {
    // in to out full
    String sequences[] = {"34", "25", "16", "07"};
    for (int i=0; i<4; i++) {
      switchLights(sequences[i], HIGH);
      if (sensoredDelay(1)) return;
    }
    for (int i=0; i<4; i++) {
      switchLights(sequences[i], LOW);
      if (sensoredDelay(1)) return;
    }
  } else if (program == 12) {
    // left to right two lights
    digitalWrite(lightPins[0], HIGH);
    if (sensoredDelay(1)) return;
    digitalWrite(lightPins[1], HIGH);
    if (sensoredDelay(1)) return;
    for (int i=1; i<7; i++) {
      digitalWrite(lightPins[i-1], LOW);
      digitalWrite(lightPins[i], HIGH);
      digitalWrite(lightPins[i+1], HIGH);
      if (sensoredDelay(1)) return;
    }
    digitalWrite(lightPins[6], LOW);
    if (sensoredDelay(1)) return;
    digitalWrite(lightPins[7], LOW);
    if (sensoredDelay(1)) return;
  } else if (program == 13) {
    // right to left two lights
    digitalWrite(lightPins[7], HIGH);
    if (sensoredDelay(1)) return;
    digitalWrite(lightPins[6], HIGH);
    if (sensoredDelay(1)) return;
    for (int i=6; i>0; i--) {
      digitalWrite(lightPins[i+1], LOW);
      digitalWrite(lightPins[i], HIGH);
      digitalWrite(lightPins[i-1], HIGH);
      if (sensoredDelay(1)) return;
    }
    digitalWrite(lightPins[1], LOW);
    if (sensoredDelay(1)) return;
    digitalWrite(lightPins[0], LOW);
    if (sensoredDelay(1)) return;
  } else if (program == 14) {
    // kitt for remote
    switchLights("01234567", HIGH);
    if (sensoredDelay(10)) return;
    switchLights("01234567", LOW);
    if (sensoredDelay(15)) return;
    for (int i=0; i<7; i++) {
      digitalWrite(lightPins[i], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i+1], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i], LOW);
      if (sensoredDelay(2)) return;
    }
    for (int i=7; i>0; i--) {
      digitalWrite(lightPins[i], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i-1], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i], LOW);
      if (sensoredDelay(2)) return;
    }
    digitalWrite(lightPins[0], LOW);
    if (sensoredDelay(1200)) return;
  } else {
    // kitt
    for (int i=0; i<7; i++) {
      digitalWrite(lightPins[i], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i+1], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i], LOW);
      if (sensoredDelay(2)) return;
    }
    for (int i=7; i>0; i--) {
      digitalWrite(lightPins[i], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i-1], HIGH);
      if (sensoredDelay(1)) return;
      digitalWrite(lightPins[i], LOW);
      if (sensoredDelay(2)) return;
    }
  }
}

void switchLights(String leds, boolean value) {
  for (int i=0; i<leds.length(); i++) {
    int led = leds[i] - '0';
    digitalWrite(lightPins[led], value);
  }
}

boolean sensoredDelay(int factor) {
  unsigned long startTime = millis();
  unsigned long time = msMinPerProgram[program] * factor;
  while (millis() - startTime < time) {
    time = map(analogRead(speedPin), 1023, 0, msMinPerProgram[program], msMaxPerProgram[program]) * factor;
    if (millis() - programSwitchTime > programSwitchDelay && digitalRead(programPin) == HIGH) {
      program = program + 1;
      if (program == (sizeof(msMinPerProgram)/sizeof(int))) {
        program = 0;
      }
      switchLights("01234567", LOW);
      programSwitchTime = millis();

      return true;
    }
  }
  
  return false;
}
