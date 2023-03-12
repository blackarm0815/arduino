void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void blinkTime() {
  // millis() gives you how many milliseconds since the arduino started running
  int seconds = millis() / 1000;
  // % is the modulus symbol it gives you the remainder when you divide by a number
  // if you % 2 then even numbers return zero and odd numbers return 1
  if (seconds % 2 == 0) {
    // turn the LED on
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // turn the LED off
    digitalWrite(LED_BUILTIN, LOW);   
  }
}

void loop() {
  // call the blinkTime function on the main loop. it has no delays, so it does not slow anything down
  blinkTime();
}
