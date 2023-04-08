// animation states
//
// 0 starting position.
// 1 forward animation.
// 2 stopped at end of forward animation.
// 3 backwards animation.

#include <Servo.h>
Servo servoAlpha;
Servo servoBeta;

bool wasButtonLow = true;

int animationStage = 0;

int animationCycleBackward = 0;
int animationCycleForward = 0;

int servoPositionAlpha = 0;
int servoPositionBeta = 0;

int cycleMax = 32000;

void setup() {
  servoAlpha.attach(10);
  servoBeta.attach(11);
  pinMode(2, INPUT);
  Serial.begin(9600);
  servoAlpha.write(55);
  servoBeta.write(55);
}

// forward

void incrementForwardAnimation() {
  if (animationCycleForward < cycleMax) {
    animationCycleForward += 1;
  }
  else {
    animationStage = 2;
  }
}

int alphaForward() {
  if (animationCycleForward >= 0 && animationCycleForward < (cycleMax * 0.25)){
    return 55;  
  }
  if (animationCycleForward >= (cycleMax * 0.25) && animationCycleForward < (cycleMax * 0.5)){
    return map(animationCycleForward, (cycleMax * 0.25), (cycleMax * 0.5), 55, 180);
  }
  if (animationCycleForward >= (cycleMax * 0.5) && animationCycleForward < (cycleMax * 0.75)){
    return 180;
  }
  if (animationCycleForward >= (cycleMax * 0.75) && animationCycleForward <= cycleMax) {
    return map(animationCycleForward, (cycleMax * 0.75), cycleMax, 180, 145);  
  }
}

int betaForward() {
  if (animationCycleForward >= 0 && animationCycleForward < (cycleMax * 0.25)) {
    return map(animationCycleForward, 0, (cycleMax * 0.25), 55, 20);
  }
  
  if (animationCycleForward >= (cycleMax * 0.25) && animationCycleForward < (cycleMax * 0.5)) {
    return 20;
  }
  
  if (animationCycleForward >= (cycleMax * 0.5) && animationCycleForward < (cycleMax * 0.75)) {
    return map(animationCycleForward, (cycleMax * 0.5), (cycleMax * 0.75), 20, 145);
  }

  if (animationCycleForward >= (cycleMax * 0.75) && animationCycleForward <= cycleMax) {
    return 145;
  }
}

// backward

void incrementBackAnimation() {
  if (animationCycleBackward < cycleMax) {
    animationCycleBackward += 1;
  }
  else {
    animationStage = 0;
  }
}

int alphaBack() {
  if (animationCycleBackward >= 0 && animationCycleBackward < (cycleMax * 0.25)) {
    return map(animationCycleBackward, 0, (cycleMax * 0.25), 145, 180); 
  }

  if (animationCycleBackward >= (cycleMax * 0.25) && animationCycleBackward < (cycleMax * 0.5)) {
    return 180;
  }

  if (animationCycleBackward >= (cycleMax * 0.5) && animationCycleBackward <= (cycleMax * 0.75)) {
    return map(animationCycleBackward, (cycleMax * 0.5), (cycleMax * 0.75), 180, 55);
  }

  if (animationCycleBackward >= (cycleMax * 0.75) && animationCycleBackward <= cycleMax) {
    return 55;
  }
}

int betaBack() {
  if (animationCycleBackward >= 0 && animationCycleBackward < (cycleMax * 0.25)) {
    return 145;
  }

  if (animationCycleBackward >= (cycleMax * 0.25) && animationCycleBackward < (cycleMax * 0.5)) {
    return map(animationCycleBackward, (cycleMax * 0.25), (cycleMax * 0.5), 145, 20); 
  }

  if (animationCycleBackward >= (cycleMax * 0.5) && animationCycleBackward <= (cycleMax * 0.75)) {
    return 20;
  }
  if (animationCycleBackward >= (cycleMax * 0.75) && animationCycleBackward <= cycleMax) {
    return map(animationCycleBackward, (cycleMax * 0.75), cycleMax, 20, 55);
  }
}

// serial monitor

void showValues() {
  //char buffer[200];
  //sprintf(buffer, " %d   %03d  %03d  %03d  %03d\n", animationStage, animationCycleForward, animationCycleBackward, servoPositionAlpha, servoPositionBeta);
  // sprintf(buffer, " %d  animationCycleForward %03d servoPositionAlpha %03d animationCycleBackward %03d servoPositionBeta %03d\n", animationStage, animationCycleForward, servoPositionAlpha, animationCycleBackward, servoPositionBeta);
  //Serial.write(buffer);
}

void buttonPressed() {
  // trigger the forward animation
  if (animationStage == 0) {
    animationStage = 1;
    animationCycleForward = 0;
    // servoAlpha.attach(10);
    // servoBeta.attach(11);
  }
  // trigger the backward animation
  if (animationStage == 2) {
    animationStage = 3;
    animationCycleBackward = 0;
    // servoAlpha.attach(10);
    // servoBeta.attach(11);
  }
  // if the button is pressed while an animation is in progress (1 or 3) it is ignored
}

void checkAnimationButton() {
  if (digitalRead(2) == LOW) {
    wasButtonLow = true;
  }
  if (digitalRead(2) == HIGH && wasButtonLow) {
    wasButtonLow = false;
    buttonPressed();
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
  showValues();
}

void loop() {
  animation();
}
