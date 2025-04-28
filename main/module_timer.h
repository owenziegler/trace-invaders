/*
timer.h

Owen Ziegler
2025 04 09

Description:
Header file for the Line Bot Timer Module.
The Timer module is meant to mimic a stopwatch in its interface.
Contains declarations of all Timer functions.
*/

#ifndef MODULE_TIMER_H
#define MODULE_TIMER_H

#include <Arduino.h>

class Timer {
  public:
    //constructor
    Timer();
    //start the timer
    void start();
    //stop, reset the timer, and return the recorded time in a float.
    float stop();

  private:
    //starting time
    unsigned long start;
};

#endif