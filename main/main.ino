/*
main.ino

Owen Ziegler
2025 02 26

Description:
Main driver file for Trace Invaders robot code. Contains the main loop & brings module files together.
*/

#include <SparkFun_TB6612.h>
#include <module_ir.h>
#include <stdint.h>
#include <Arduino.h>
#include <utils.h>
#include <string>

//motor driver pins
#define AIN1 10
#define AIN2 11
#define PWMA 12
#define BIN1 18
#define BIN2 17
#define PWMB 16
#define STBY 9

uint8_t lineState;

void setup() {
  Serial.begin(115200);
  irSetup();
}

void loop() {
  lineState = getLineState();
  Serial.print(uint8ToBinary(lineState));
  Serial.print("\n");
  //centered
  if(lineState == 0b00000100) {
    //drive straight forward
  }
  //slight left
  else if(lineState == 0b00001000) {
    //slight adjust to the left
  }
  //slight right
  else if(lineState == 0b00000010) {
    //slight adjust to the right
  }
  //big left
  else if(lineState == 0b00010000) {
    //big adjust to the left
  }
  //big right
  else if(lineState == 0b00000001) {
    //big adjust to the right
  }
  delay(100);
}
