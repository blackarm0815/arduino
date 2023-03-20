// the length of the animation in milliseconds.
const int animationLength = 8000L;
// when the button is pressed, this is made equal to the current time. the animation starts from there.
int unsigned long timerPoint = 0L;
// this is made true when the button is pressed, to avoid an animation happening when the arduino turns on.
bool timerActive = false;
// the number of milliseconds into the animation. if the animation is not running, it will be zero.
int animationTime = 0;
// position of the server from 0 to 180
int long servoPosition = 0L;

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
  if (millis() > (timerPoint + animationLength)) {
    return 0;
  }
  // calculate the animationTime between the start time and current time    
  int calcTime = millis() - timerPoint;
  // if the calcTime is greater than the length of the animation return zero. it is over.
  if (calcTime > animationLength) {
    calcTime = 0;
  }
  // if the code gets this far, the animation is still in progress, return the 
  return calcTime;
}

int calcServoPosition() {
  int long foo = 0;
  // move to 180 for the first half
  if (animationTime < (animationLength / 2)) {
    foo = ((animationTime * 360L) / animationLength);
  }
  // move from 180 back to 0 for the second half
  else {
    foo = ((animationLength - animationTime) * 360L / animationLength);
  }
  return foo;
}

void showValues() {
  Serial.print(timerActive);
  Serial.print(' ');
  Serial.print(millis());
  Serial.print(' ');
  Serial.print(timerPoint);
  Serial.print(' ');
  Serial.print(animationTime);
  Serial.print(' ');
  Serial.print(servoPosition);
  Serial.print("\n");
}

void loop() {
  buttonCheck();
  animationTime = calcAnimationTime();
  servoPosition = calcServoPosition();
  showValues();
}
