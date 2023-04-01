#include <Servo.h>
Servo servoAlpha;
Servo servoBeta;
int backAnimation = 0;
int buttonCount = 0;
int forwardAnimation = 0;
int servoPositionAlpha = 0;
int servoPositionBeta = 0;

void setup() {
  servoAlpha.attach(10);
  servoBeta.attach(11);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void incrementForwardAnimation() {
  if (forwardAnimation > 0) {
    forwardAnimation += 1;
  }
  if (forwardAnimation == 300) {
    forwardAnimation = 0;
  }
}

void incrementBackAnimation() {
  if (backAnimation > 0) {
    backAnimation += 1;
  }
  if (backAnimation == 300) {
    backAnimation = 0;
  }
}

void showValues() {
  char buffer[30];
  sprintf(buffer, "%03d %03d %03d %03d %03d\n", buttonCount, forwardAnimation, servoPositionAlpha, backAnimation, servoPositionBeta);
  Serial.write(buffer);
}

int alphaForward() {
  if (forwardAnimation > 0 && forwardAnimation < 200) {
    return map(forwardAnimation, 0, 200, 0, 180);
  }
  if (forwardAnimation >= 201 && forwardAnimation < 300) {
    return 180;
  }
}

int betaForward() {
  if (forwardAnimation >= 0 && forwardAnimation < 200) {
    return 0;
  }
  if (forwardAnimation >= 201 && forwardAnimation < 300) {
    return map(forwardAnimation, 201, 300, 0, 90);
  }
}

int alphaBack() {
  if (backAnimation >= 0 && backAnimation < 100) {
    return 180;
  }
  if (backAnimation >= 101 && backAnimation < 300) {
    return map(backAnimation, 101, 300, 180, 0);
  }
}

int betaBack() {
  if (backAnimation > 0 && backAnimation < 100) {
    return map(backAnimation, 0, 100, 90, 0);
  }
  if (backAnimation >= 101 && backAnimation < 300) {
    return 0;
  }
}

void startAnimationButton() {
  if (digitalRead(2) == HIGH) {
    delay(400);
    if (buttonCount == 0) {
      buttonCount = 1;
      forwardAnimation = 1;
      backAnimation = 0;
    } else {
      buttonCount = 0;
      forwardAnimation = 0;
      backAnimation = 1;
    }
  } 
}

void animation(){
  startAnimationButton();
  if (buttonCount == 1 && forwardAnimation > 0) {
     servoPositionAlpha = alphaForward();
     servoPositionBeta = betaForward();
  } 
  if (buttonCount == 0 && backAnimation > 0) {
    servoPositionAlpha = alphaBack();
    servoPositionBeta = betaBack();
  }
  servoAlpha.write(servoPositionAlpha);
  servoBeta.write(servoPositionBeta);
  showValues();
  incrementForwardAnimation();
  incrementBackAnimation();
}

void loop() {
  animation();
}
