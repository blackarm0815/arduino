// the length of the animation in milliseconds.
const int loopMax = 2000;
// when the button is pressed, this is made equal to the current time. the animation starts from there.
int unsigned long timerPoint = 0;
// this is made true when the button is pressed, to avoid an animation happening when the arduino turns on.
bool timerActive = false;
// the number of milliseconds into the animation. if the animation is not running, it will be zero.
int animationTime = 0;

void setup() {
  // set up pin 2 for the button
  pinMode(2, INPUT);
  // activate the serial monitor
  Serial.begin(9600);
}

void buttonCheck() {
  // if the button is pressed
  if (digitalRead(2) == HIGH) {
    // move the timerPoint to match the current time, starting the animation
    timerPoint = millis();
    // making this true allows animation calculations to happen
    timerActive = true;
  } 
}

int calcAnimationTime() {
  // before the button is pressed, always return zero  
  if (!timerActive) {
    return 0;
  }
  // if the button has been pressed, run calculations
  else {
    // calculate the animationTime between the start time and current time    
    int animationTime = millis() - timerPoint;
    // if the animationTime is greater than the length of the animation return zero. it is over.
    if (animationTime > loopMax) {
      animationTime = 0;
    }
    // if the code gets this far, the animation is still in progress, return the 
    return animationTime;
  }
}

void showValues() {
  Serial.print(timerActive);
  Serial.print(' ');
  Serial.print(millis());
  Serial.print(' ');
  Serial.print(timerPoint);
  Serial.print(' ');
  Serial.print(animationTime);
  Serial.print("\n");
}

void loop() {
  buttonCheck();
  animationTime = calcAnimationTime();
  showValues();
}
