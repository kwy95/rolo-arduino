const uint8_t sens[2] = { 2, 7 };
bool midPulse[2] = { false, false };
int lastValue[2];
int currentValue[2];
unsigned long timeStart[2];
unsigned long diff[2];
const char* bikeNames[2] = { "bike0", "bike1" };

void setup() {
  const long baud = 115200L;

  Serial.begin(baud);
  pinMode(sens[0], INPUT);
  pinMode(sens[1], INPUT);
  establishContact();

  delay(1000UL);

  lastValue[0] = 1;
  lastValue[1] = 1;
  // Serial.print("{Started: ");
  // Serial.print(lastValue[0]);
  // Serial.print("; ");
  // Serial.print(lastValue[1]);
  // Serial.print("}");
}

void loop() {
  const char* currentTimeKey = "current_time";
  const unsigned long minPulse = 10000UL;
  unsigned long currentTime;

  currentValue[0] = digitalRead(sens[0]);
  currentValue[1] = digitalRead(sens[1]);
  currentTime = micros();

  for (int i = 0; i < 2; i++) {
    if (currentValue[i] != lastValue[i]) {
      midPulse[i] = !midPulse[i];
      if (midPulse[i]) {
        timeStart[i] = currentTime;
      } else {
        diff[i] = currentTime - timeStart[i];
        if (diff[i] >= minPulse) {
          Serial.print("{");
          Serial.print(i);
          Serial.print(";");
          Serial.print(diff[i]);
          Serial.print(";");
          Serial.print(currentTime);
          Serial.print("}");
        }
      }
      lastValue[i] = currentValue[i];
    }
  }
}

void establishContact() {
  while (!Serial) continue;

  while (Serial.available() <= 0 || Serial.read() != 'A') {
    Serial.print('A');  // send a capital A
    delay(300UL);
  }

  Serial.flush();
}
