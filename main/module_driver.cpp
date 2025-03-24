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

void drive() {
  //drive forward
}

void left() {
  //turn left
}

void right() {
  //turn right
}

void reverse() {
  //go backward
}

void nudgeleft() {
  //slightly adjust left
}

void nudgeright() {
  //slightly adjust right
}