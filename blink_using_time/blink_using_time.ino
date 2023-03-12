void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void blinkTime() {
  int seconds = millis() / 1000;
  if (seconds % 2 == 0) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  }
}

void loop() {
  blinkTime();
}
