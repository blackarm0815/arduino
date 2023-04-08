// animation states
//

// the servo library
#include <Servo.h>
// create the servo objects
Servo servoAlpha;
Servo servoBeta;
// this keeps track of when the button was not pressed is used to make sure that the button actions do not happen every cycle
// only on the first cycle the button is pressed, when wasButtonLow is still true
bool wasButtonLow = true;
// 0 starting position.
// 1 forward animation.
// 2 stopped at end of forward animation.
// 3 backwards animation.
int animationStage = 0;
// the cycle counts for the forward and backward animations
int animationCycleBackward = 0;
int animationCycleForward = 0;
// variables for storing the servos angles in degrees
int servoPositionAlpha = 0;
int servoPositionBeta = 0;
// the full length of the animation in cycles
// an unsigned int is used because it has a maximum value of 65,535
// unlike a regular int that has a range of -32,768 to 32,767
unsigned int cycleMax = 50000;
//
void setup() {
  // activate the servos
  servoAlpha.attach(10);
  servoBeta.attach(11);
  // set up the button
  pinMode(2, INPUT);
  // enable serial console (currently disabled)
  // Serial.begin(9600);
}

void incrementForwardAnimation() {
  // forward
  if (animationCycleForward < cycleMax) {
    animationCycleForward += 1;
  }
  else {
    // when the forward animation (stage 1) is complete, change to the resting stage 2
    animationStage = 2;
  }
}

int alphaForward() {
  if (animationCycleForward >= 0 && animationCycleForward < (cycleMax * 0.2)){
    return 55;  
  }
  if (animationCycleForward >= (cycleMax * 0.2) && animationCycleForward < (cycleMax * 0.5)){
    return map(animationCycleForward, (cycleMax * 0.2), (cycleMax * 0.5), 55, 180);
  }
  if (animationCycleForward >= (cycleMax * 0.5) && animationCycleForward < (cycleMax * 0.8)){
    return 180;
  }
  if (animationCycleForward >= (cycleMax * 0.8) && animationCycleForward <= cycleMax) {
    return map(animationCycleForward, (cycleMax * 0.8), cycleMax, 180, 145);  
  }
}

int betaForward() {
  if (animationCycleForward >= 0 && animationCycleForward < (cycleMax * 0.2)) {
    return map(animationCycleForward, 0, (cycleMax * 0.2), 55, 20);
  }
  
  if (animationCycleForward >= (cycleMax * 0.2) && animationCycleForward < (cycleMax * 0.5)) {
    return 20;
  }
  
  if (animationCycleForward >= (cycleMax * 0.5) && animationCycleForward < (cycleMax * 0.8)) {
    return map(animationCycleForward, (cycleMax * 0.5), (cycleMax * 0.8), 20, 145);
  }

  if (animationCycleForward >= (cycleMax * 0.8) && animationCycleForward <= cycleMax) {
    return 145;
  }
}

void incrementBackAnimation() {
  // backward
  if (animationCycleBackward < cycleMax) {
    animationCycleBackward += 1;
  }
  else {
    // when the backward animation (stage 3) is complete, change to the resting stage 0
    animationStage = 0;
  }
}

int alphaBack() {
  if (animationCycleBackward >= 0 && animationCycleBackward < (cycleMax * 0.2)) {
    return map(animationCycleBackward, 0, (cycleMax * 0.2), 145, 180); 
  }

  if (animationCycleBackward >= (cycleMax * 0.2) && animationCycleBackward < (cycleMax * 0.5)) {
    return 180;
  }

  if (animationCycleBackward >= (cycleMax * 0.5) && animationCycleBackward <= (cycleMax * 0.8)) {
    return map(animationCycleBackward, (cycleMax * 0.5), (cycleMax * 0.8), 180, 55);
  }

  if (animationCycleBackward >= (cycleMax * 0.8) && animationCycleBackward <= cycleMax) {
    return 55;
  }
}

int betaBack() {
  if (animationCycleBackward >= 0 && animationCycleBackward < (cycleMax * 0.2)) {
    return 145;
  }

  if (animationCycleBackward >= (cycleMax * 0.2) && animationCycleBackward < (cycleMax * 0.5)) {
    return map(animationCycleBackward, (cycleMax * 0.2), (cycleMax * 0.5), 145, 20); 
  }

  if (animationCycleBackward >= (cycleMax * 0.5) && animationCycleBackward <= (cycleMax * 0.8)) {
    return 20;
  }
  if (animationCycleBackward >= (cycleMax * 0.8) && animationCycleBackward <= cycleMax) {
    return map(animationCycleBackward, (cycleMax * 0.8), cycleMax, 20, 55);
  }
}

void showValues() {
  // currently disabled because it massively increases the cycle time, causing stutter
  char buffer[200];
  sprintf(buffer, " %d   %03d  %03d  %03d  %03d\n", animationStage, animationCycleForward, animationCycleBackward, servoPositionAlpha, servoPositionBeta);
  Serial.write(buffer);
}

void buttonPressed() {
  // trigger the forward animation if the current stage is zero
  if (animationStage == 0) {
    animationStage = 1;
    animationCycleForward = 0;
  }
  // trigger the backward animation if the current stage is two
  if (animationStage == 2) {
    animationStage = 3;
    animationCycleBackward = 0;
  }
  // if the button is pressed while an animation is in progress (1 or 3) it is ignored
}

void checkAnimationButton() {
  // if the button is currently unpressed, keep a record
  if (digitalRead(2) == LOW) {
    wasButtonLow = true;
  }
  // if the button has been pressed and was not pressed on the last cycle, take action
  if (digitalRead(2) == HIGH && wasButtonLow) {
    buttonPressed();
    // record that the button is no longer low, to stop the action happening again while the button is pressed
    wasButtonLow = false;
  }
}

void animation(){
  checkAnimationButton();
  // start position
  if (animationStage == 0) {
    servoPositionAlpha = 55;
    servoPositionBeta = 55;
  }
  // forward animation
  if (animationStage == 1) {
    incrementForwardAnimation();
    servoPositionAlpha = alphaForward();
    servoPositionBeta = betaForward();
  }
  // backward animation
  if (animationStage == 3) {
    incrementBackAnimation();
    servoPositionAlpha = alphaBack();
    servoPositionBeta = betaBack();
  }
  // move servos
  servoAlpha.write(servoPositionAlpha);
  servoBeta.write(servoPositionBeta);
  // showValues();
}

void loop() {
  animation();
}
