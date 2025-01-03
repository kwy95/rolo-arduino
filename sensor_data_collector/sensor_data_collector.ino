const long baud = 115200;
const unsigned long minPulse = 1000;

const uint8_t sen1 = 2;
const uint8_t sen2 = 7;
bool midPulse1 = false;
bool midPulse2 = false;
int lastValue1;
int lastValue2;
int currentValue1;
int currentValue2;
unsigned long currentTime;
unsigned long timeStart1;
unsigned long timeStart2;
unsigned long diff1;
unsigned long diff2;

void setup()
{
  Serial.begin(baud);
  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);

  delay(1000);
  lastValue1 = digitalRead(sen1);
  lastValue2 = digitalRead(sen2);
  Serial.print("Started: ");
  Serial.print(lastValue1);
  Serial.print("; ");
  Serial.println(lastValue2);
}

void loop()
{
  currentValue1 = digitalRead(sen1);
  currentValue2 = digitalRead(sen2);
  currentTime = micros();

  if (currentValue1 != lastValue1) {
    midPulse1 = !midPulse1;
    if (midPulse1) {
      timeStart1 = currentTime;
    } else {
      diff1 = currentTime - timeStart1;
      if (diff1 >= minPulse) {
        Serial.print("bike1: ");
        Serial.println(diff1);
      }
    }
    lastValue1 = currentValue1;
  }

  if (currentValue2 != lastValue2) {
    midPulse2 = !midPulse2;
    if (midPulse2) {
      timeStart2 = currentTime;
    } else {
      diff2 = currentTime - timeStart2;
      if (diff2 >= minPulse) {
        Serial.print("bike2: ");
        Serial.println(diff2);
      }
    }
    lastValue2 = currentValue2;
  }
}