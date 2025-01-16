const uint8_t sens[2] = { 2, 7 };
bool midPulse[2] = { false, false };
int lastValue[2];
int currentValue[2];
unsigned long timeStart[2];
unsigned long diff[2];

void setup() {
  const long baud = 115200;

  Serial.begin(baud);
  pinMode(sens[0], INPUT);
  pinMode(sens[1], INPUT);
  establishContact();

  delay(1000);

  lastValue[0] = digitalRead(sens[0]);
  lastValue[1] = digitalRead(sens[1]);
  Serial.print("Started: ");
  Serial.print(lastValue[0]);
  Serial.print("; ");
  Serial.println(lastValue[1]);
}

void loop() {
  const int minPulse = 1000;
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
          Serial.print("bike");
          Serial.print(i);
          Serial.print(": ");
          Serial.println(diff[i]);
        }
      }
      lastValue[i] = currentValue[i];
    }
  }
}

void establishContact() {
  while (!Serial) continue;

  while (Serial.available() <= 0 || Serial.read() != 65) {
    Serial.print('A');  // send a capital A
    delay(300);
  }

  Serial.flush();
}
