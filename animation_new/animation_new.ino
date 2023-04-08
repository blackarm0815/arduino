// animation states
//
// 0 starting position.
// 1 forward animation.
// 2 stopped at end of forward animation.
// 3 backwards animation.

#include <Servo.h>
Servo servoAlpha;
Servo servoBeta;
int animationCycleBackward = 0;
int animationCycleForward = 0;
int animationStage = 0;
int servoPositionAlpha = 0;
int servoPositionBeta = 0;
bool wasButtonLow = true;

void setup() {
  servoAlpha.attach(10);
  servoBeta.attach(11);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

// forward

void incrementForwardAnimation() {
  if (animationCycleForward < 100) {
    animationCycleForward += 1;
  }
  else {
    animationStage = 2;
  }
}

int alphaForward() {
  if (animationCycleForward >= 0 && animationCycleForward < 50) {
    return map(animationCycleForward, 0, 50, 0, 180);
  }
  if (animationCycleForward >= 50 && animationCycleForward <= 100) {
    return 180;
  }
}

int betaForward() {
  if (animationCycleForward >= 0 && animationCycleForward < 50) {
    return 0;
  }
  if (animationCycleForward >= 50 && animationCycleForward <= 100) {
    return map(animationCycleForward, 50, 100, 0, 90);
  }
}

// backward

void incrementBackAnimation() {
  if (animationCycleBackward < 100) {
    animationCycleBackward += 1;
  }
  else {
    animationStage = 0;
  }
}

int alphaBack() {
  if (animationCycleBackward >= 0 && animationCycleBackward < 50) {
    return 180;
  }
  if (animationCycleBackward >= 50 && animationCycleBackward <= 100) {
    return map(animationCycleBackward, 50, 100, 180, 0);
  }
}

int betaBack() {
  if (animationCycleBackward >= 0 && animationCycleBackward < 50) {
    return map(animationCycleBackward, 0, 50, 90, 0);
  }
  if (animationCycleBackward >= 50 && animationCycleBackward <= 100) {
    return 0;
  }
}

// serial monitor

void showValues() {
  char buffer[200];
  sprintf(buffer, "%d %03d %03d %03d %03d\n", animationStage, animationCycleForward, servoPositionAlpha, animationCycleBackward, servoPositionBeta);
  Serial.write(buffer);
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
    servoPositionAlpha = 0;
    servoPositionBeta = 0;
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
