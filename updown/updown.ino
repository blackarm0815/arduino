void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
int calculateUpDown() {
  // use modulus to get a value that goes from 0 - 9999
  int zeroToMax = millis() % 10000;
  if (zeroToMax < 5000) {
    // return 0 to 4999
    return zeroToMax;
  } else {
    // return 500 > 0
    return 10000 - zeroToMax;
  }
}

void backAndForth() {
  int output = calculateUpDown();
  Serial.print(output);
  Serial.print("\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  backAndForth();
}
