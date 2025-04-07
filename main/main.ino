/*
main.ino

Owen Ziegler
2025 02 26

Description:
Main driver file for Trace Invaders robot code. Contains the main loop & brings module files together.
*/

#include <SparkFun_TB6612.h>
#include <module_ir.h>
#include <module_driver.h>
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

#define BUTTON 0

uint8_t lineState;
bool running = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);
  irSetup();
  driverSetup();
}

void loop() {
  lineState = getLineState();
  Serial.print(uint8ToBinary(lineState) + "\n");
  Serial.print((digitalRead(BUTTON) == HIGH) + "\n");
  Serial.print(running + "\n");

  if(running) {
    switch(lineState) {
      //center
      case 0b11011:
        drive(256,256);
        break;
      //left 1
      case 0b10011:
        drive(196,256);
        break;
      //left 2
      case 0b10111:
        drive(64,256);
        break;
      //left 3 & 4
      case 0b00111:
      case 0b01111:
        drive(32,196);
        break;  
      //right 1
      case 0b11001:
        drive(256,196);
        break;
      //right 2
      case 0b11101:
        drive(256,64);
        break;
      //right 3 & 4
      case 0b11100:
      case 0b11110:
        drive(196,32);
        break;
      //any other state
      default:
        drive(192,192);
        break;
    }
  }
  else {
    drive(0,0);
  }
  if (!digitalRead(BUTTON)) {
    running = !running;
    delay(250);
  }
  delay(50);
}
