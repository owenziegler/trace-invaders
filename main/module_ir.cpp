/*
module_ir.c

Owen Ziegler
2025 02 26

Description:
IR sensor module for Trace Invaders linebot. Contains functions pertaining to the IR sensor module.
*/

#include "module_ir.h"
#include <Arduino.h>
#include <stdint.h>

//IR sensor pins
#define IR0 19
#define IR1 20
#define IR2 21
#define IR3 47
#define IR4 48
#define NUM_SENSORS 5

void irSetup() {
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
}

uint8_t getLineState() {
  uint8_t lineState = 0;
  lineState |= (digitalRead(IR0) << 4);
  lineState |= (digitalRead(IR1) << 3);
  lineState |= (digitalRead(IR2) << 2);
  lineState |= (digitalRead(IR3) << 1);
  lineState |= (digitalRead(IR4) << 0);
  return lineState;
}