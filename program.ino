byte lightPins[8] = {0, 1, 2, 3, 4, 8, 9, 10};
byte programPin = 8;
byte speedPin = A7;

byte allLights[8] = {0, 1, 2, 3, 4, 5, 6, 7};
byte halfLights[2][4] = {
  {0, 1, 2, 3},
  {4, 5, 6, 7}
};
byte splittedBounce[6] = {0, 1, 2, 3, 2, 1};
byte splittedLights[4][4][2] = {
  {{3, 4}, {2, 5}, {1, 6}, {0, 7}},
  {{3, 7}, {2, 6}, {1, 5}, {0, 4}},
  {{0, 7}, {1, 6}, {2, 5}, {3, 4}},
  {{0, 4}, {1, 5}, {2, 6}, {3, 7}}
};

volatile byte program = 0;
unsigned long programSwitchTime = 0;

void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(lightPins[i], OUTPUT);
  }  
  pinMode(programPin, INPUT);

  flasher(20, 6);
}

void loop() {
  if (program == 1 || program == 2) {
    // flasher / flasher 2 times
    flasher(6, (program == 2) ? 3 : 6);
    if (program == 2) {
      flasher(6, 12);
    }
  } else if (program == 3) {
    // police
    switchLights(halfLights[0], 4, 1);
    switchLights(halfLights[1], 4, 0);
    sensoredDelay(8);
    switchLights(halfLights[0], 4, 0);
    switchLights(halfLights[1], 4, 1);
    sensoredDelay(8);
  } else if (program == 4) {
    // police 2 times
    for (byte l = 0; l < 2; l++) {
      for (byte i = 1; i < 5; i++) {
        switchLights(halfLights[l], 4, i % 2);
        sensoredDelay(4);
      }
      sensoredDelay(2);
    }
  } else if (program == 5 || program == 6) {
    // splitted one out to in bounce / splitted one left to right bounce 
    for (byte i = 0; i < 6; i++) {
      switchLights(splittedLights[program - 5][splittedBounce[i]], 2, 1);
      sensoredDelay(4);
      switchLights(splittedLights[program - 5][splittedBounce[i]], 2, 0);
    }
  } else if (program >= 7 && program <= 10) {
    // splitted out to in snake / splitted left to right snake
    // splitted in to out snake / splitted right to left snake
    for (byte value = 1; value >= 0; value--) {
      for (byte i = 0; i < 4; i++) {
        switchLights(splittedLights[program - 7][i], 2, value);
        sensoredDelay(4);
      }
    }
  } else if (program >= 11 && program <= 14) {
    // splitted out to in full, off / splitted left to right full, off
    // splitted in to out full, off / splitted right to left full, off
    for (byte i = 0; i < 4; i++) {
      switchLights(splittedLights[program - 11][i], 2, 1);
      sensoredDelay(4);
    }
    switchLights(allLights, 8, 0);
    sensoredDelay(8);
  } else if (program == 15) {
    // snake
    for (byte value = 1; value >= 0; value--) {
      for (byte i = 0; i < 8; i++) {
        digitalWrite(lightPins[i], value);
        sensoredDelay(2);
      }
    } 
  } else if (program == 16) {
    // snake reverse
    for (byte value = 1; value >= 0; value--) {
      for (byte i = 7; i >= 0; i--) {
        digitalWrite(lightPins[i], value);
        sensoredDelay(2);
      }
    }
  } else if (program == 0 || program == 17) {
    // kitt // kitt with 2 min delay
    if (program == 17) {
      interruptedDelay(120000);
    }
    for (byte i = 0; i < 7; i++) {
      digitalWrite(lightPins[i], 1);
      sensoredDelay(1);
      digitalWrite(lightPins[i+1], 1);
      sensoredDelay(1);
      digitalWrite(lightPins[i], 0);
      sensoredDelay(2);
    }
    for (byte i = 7; i > 0; i--) {
      digitalWrite(lightPins[i], 1);
      sensoredDelay(1);
      digitalWrite(lightPins[i-1], 1);
      sensoredDelay(1);
      digitalWrite(lightPins[i], 0);
      sensoredDelay(2);
    }
  }
}

void flasher(byte firstFactor, byte secondFactor) {
  switchLights(allLights, 8, 1);
  sensoredDelay(firstFactor);
  switchLights(allLights, 8, 0);
  sensoredDelay(secondFactor);
}

void switchLights(byte lights[], byte count, byte value) {
  for (byte i = 0; i < count; i++) {
    digitalWrite(lightPins[lights[i]], value);
  }
}

void sensoredDelay(byte factor) {
  unsigned long startTime = millis();
  short poti = analogRead(speedPin);
  short ms = (poti / 12 + 10) * factor;
  interruptedDelay(ms);
}

void interruptedDelay(int ms) {
  unsigned long startTime = millis();
  while (millis() - startTime < ms) {
    if (millis() - programSwitchTime > 500 && digitalRead(programPin) == 1) {
      program++;
      if (program > 17) {
        program = 0;
      }
      switchLights(allLights, 8, 0);
      programSwitchTime = millis();

      return;
    }
  }
}
