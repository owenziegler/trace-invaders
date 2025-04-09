/*
timer.h

Owen Ziegler
2025 04 09

Description:
Header file for the Line Bot Timer Module. Contains declarations of all Timer functions
*/

#ifndef MODULE_TIMER_H
#define MODULE_TIMER_H

#include <Arduino.h>

class Timer {
  public:
    //constructor
    Timer();
    //get the current time in seconds (float)
    float getCurrent_s();
    //get the current time in milliseconds (unsigned long)
    unsigned long getCurrent_ms();
    //get the starting time
    unsigned long getStart();
    //reset the timer
    void reset();
  private:
    //starting time
    unsigned long start;
}

#endif