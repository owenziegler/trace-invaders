#include <Arduino.h>

#define AIN1 10
#define AIN2 11
#define PWMA 12
#define BIN1 18
#define BIN2 17
#define PWMB 16
#define STBY 9

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);
}

void loop() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, 55);
  delay(7000);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, 55);
  delay(7000);

  analogWrite(PWMA, 0);
  delay(3000);

  analogWrite(PWMB, 0);
  delay(3000);
}
