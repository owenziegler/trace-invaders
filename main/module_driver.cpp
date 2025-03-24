/*
module_driver.cpp

Joel Osho & Owen Ziegler
3/19/2025

Description:
Motor driver functions for Line Follower robot. Contains definitions of all motor driver-related functions
*/

#include "module_driver.h"
#include <Arduino.h>

//pin definitions
#define AIN1 10
#define AIN2 11
#define PWMA 12
#define BIN1 18
#define BIN2 17
#define PWMB 16
#define STBY 9

void driverSetup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
}

// Set up motors

void setMotorA(int speed) {
  if (speed >= 0) {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    speed = -speed;
  }
  analogWrite(PWMA, constrain(speed, 0, 255));
}

void setMotorB(int speed) {
  if (speed >= 0) {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    speed = -speed;
  }
  analogWrite(PWMB, constrain(speed, 0, 255));
}

void nudgeLeft(int baseSpeed, int nudgeAmount) {
  setMotorA(baseSpeed - nudgeAmount);  // Left motor slower
  setMotorB(baseSpeed);   // Right motor normal
}

void nudgeRight(int baseSpeed, int nudgeAmount) {
  setMotorA(baseSpeed);                // Left motor normal
  setMotorB(baseSpeed - nudgeAmount);   // Right motor slower
  }

void loop() {
  int left = digitalRead(SENSOR_LEFT);
  int center = digitalRead(SENSOR_CENTER);
  int right = digitalRead(SENSOR_RIGHT);

  int baseSpeed = 150;
  int nudgeAmount = 30;  // Adjustable

// Drive forward
  if (center == HIGH && left == LOW && right == LOW) {
    setMotorA(baseSpeed);
    setMotorB(baseSpeed);
  } 
// Left nudge
  else if (left == HIGH && center == LOW && right == LOW) {
    nudgeLeft(baseSpeed, nudgeAmount);
  } 
// Right nude
  else if (right == HIGH && center == LOW && left == LOW) {
    nudgeRight(baseSpeed, nudgeAmount);
  } 
// More turn left
  else if (left == HIGH && center == HIGH && right == LOW) {
    setMotorA(baseSpeed / 2);
    setMotorB(baseSpeed);
  } 
// More turn right
  else if (right == HIGH && center == HIGH && left == LOW) {
    setMotorA(baseSpeed);
    setMotorB(baseSpeed / 2);
  }
  // Lost line or intersection — stop or search (go in reverse)
  else {
    setMotorA(0);
    setMotorB(0);
    delay(2);
    setMotorA(-55);
    setMotorB(-55);
  }
}