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

//motor driver pins
#define AIN1 10
#define AIN2 11
#define PWMA 12
#define BIN1 18
#define BIN2 17
#define PWMB 16
#define STBY 9

uint8_t lineState;

String uint8ToBinary(uint8_t value) {
    String binary = "";
    // Loop through each bit (from most significant to least significant)
    for (int i = 7; i >= 0; --i) {
        // Check if the bit at position i is set (1) or not (0)
        if ((value & (1 << i)) != 0) {
            binary += '1';
        } else {
            binary += '0';
        }
    }
    return binary;
}

void setup() {
  Serial.begin(115200);
  irSetup();
}

void loop() {
  lineState = getLineState();
  Serial.print(uint8ToBinary(lineState));
  Serial.print("\n");
  delay(100);
}
