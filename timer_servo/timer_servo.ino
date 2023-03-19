int loopMax = 5000;
int timerPoint = 0 - loopMax;

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void timeCheck() {
  if (digitalRead(2) == HIGH) {
    timerPoint = millis();
  } 
}

int calcDiff() {
  int diff = millis() - timerPoint;
  if (diff > loopMax) {
    diff = 0;
  }
  return diff;
}

void loop() {
  timeCheck();
  int difference = calcDiff();
  Serial.print(millis());
  Serial.print(' ');
  Serial.print(timerPoint);
  Serial.print(' ');
  Serial.print(difference);
  Serial.print("\n");
}




