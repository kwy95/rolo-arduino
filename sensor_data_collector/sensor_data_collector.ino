#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>

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

  lastValue[0] = digitalRead(sens[0]);
  lastValue[1] = digitalRead(sens[1]);
  Serial.print("\nStarted: ");
  Serial.print(lastValue[0]);
  Serial.print("; ");
  Serial.println(lastValue[1]);
}

void loop() {
  const char* currentTimeKey = "current_time";
  const unsigned long minPulse = 10000UL;
  unsigned long currentTime;
  StaticJsonDocument<12> doc[2];
  // StaticJsonDocument<24> doc[2];

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
          // doc[i][currentTimeKey] = currentTime;
          doc[i][bikeNames[i]] = diff[i];
          serializeJson(doc[i], Serial);
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
    delay(300UL);
  }

  Serial.flush();
}
