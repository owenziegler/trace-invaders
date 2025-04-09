/*
module_timer.cpp

Owen Ziegler
2025 04 09

Description:
Implementation file for timer module functions
*/

#include <module_timer.h>
#include <Arduino.h>
#include <stdint.h>

//Constructor, sets starting time (milliseconds since power-up)
Timer::Timer() {
  start = millis();
}

//gets current time in seconds as a float
float Timer::getCurrentFloat() {
  return static_cast<float>(millis() - start) / 1000;
}

//gets current time in milliseconds as an int
unsigned long Timer::getCurrentInt() {
  return millis() - start
}

//gets
unsigned long Timer::getStart() {
  return start;
}

void Timer::reset() {
  start = millis();
}