#include <Servo.h>
Servo servoAlpha;
int animationTimer = 0;
int servoPosition = 0;

void setup() {
  servoAlpha.attach(10);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void incrementAnimation() {
  if (animationTimer > 0) {
    animationTimer += 1;
  }
  if (animationTimer == 800) {
    animationTimer = 0;
  }
}

void showValues() {
  char buffer[10];
  sprintf(buffer, "%03d %03d\n", animationTimer, servoPosition);
  Serial.write(buffer);
}

int calcServoAlpha() {
  // 0 - 399
  if (animationTimer >= 0 && animationTimer < 400) {
    return map(animationTimer, 0, 400, 0, 180);
  }
  // 400 - 799
  if (animationTimer >= 400 && animationTimer < 800) {
    return map(animationTimer, 400, 800, 180, 0);
  }
}

void startAnimationButton() {
  if (digitalRead(2) == HIGH) {
    animationTimer = 1;
  } 
}

void animation(){
  startAnimationButton();
  servoAlpha.write(calcServoAlpha());
  showValues();  
  incrementAnimation();
}

void loop() {
  animation();
}



