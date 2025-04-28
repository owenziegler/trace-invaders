/*
main.ino

Owen Ziegler
2025 02 26

Description:
Main driver file for Trace Invaders robot code. Contains the main loop & brings module files together.
*/

//#include <SparkFun_TB6612.h>
#include <module_ir.h>
#include <module_driver.h>
#include <module_lcd.h>
#include <stdint.h>
#include <Arduino.h>
#include <utils.h>
#include <string>
#include <stdint.h>

//motor driver pins
#define AIN1 10
#define AIN2 11
#define PWMA 12
#define BIN1 18
#define BIN2 17
#define PWMB 16
#define STBY 9

#define BUTTON 0

//states
#define RESET 0
#define COUNTDOWN 1
#define RUNUP 2
#define LAP 3
#define LOST 4
#define FINISH


uint8_t lineState;            //
uint8_t currentState = 0;        //
uint8_t nextState = 0;
uint8_t countdownTimer = 5
bool running = 0;             //
uint32_t stateCounter = 0;         //generic counter var used by states. reset to 0 on state change
uint8_t tickCounter = 0;          //
uint8_t lostCounter;
float lapTime();
Timer timer;



void setup() {
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);
  irSetup();
  driverSetup();
  lcdSetup();
  timer = Timer();
}

//FSM state handler functions

void handleReset() {
  displayStrings("Trace Invader", "")
  //if the button is pressed, wait for it to become unpressed
  //when the button is unpressed, set nextState to COUNTDOWN
  if(!digitalRead(BUTTON)) { //if the button is pressed
    while (digitalRead(BUTTON)) { //wait for the button to become unpressed
      delay(10); //wait 10 ms between checks to reduce CPU usage
    }
    nextState = COUNTDOWN;
  }
}

void handleCountdown() {
  //while countdownTimer > 0:
  //display countdownTimer to screen
  //wait 1000 ms
  //clear screen
  //decrement countdownTimer

  //reset countdownTimer to 5
  //transition to handleRunup
  if(countdownTimer > 0) {
    if(countdownTimer > 0) {
      displayStrings("Start your engines!", to_string(countdownTimer));
      delay(1000);
      countdownTimer--;
      clearDisplay();
    }
    else {
      countdownTimer = 5;
      nextState = RUNUP;
    }
  }
}

void handleRunup() {
  //same control logic as handleLap, except when a tick is crossed,
  //nextState is set to LAP and the stopwatch is started
  lineState = getLineState();
  switch(lineState) {
    //center
    case 0b11011:
      setMotorA(192);
      setMotorB(192);
      break;
    //left 1
    case 0b10011:
      //drive(196,256);
      setMotorA(128);
      setMotorB(256);
      break;
    //left 2
    case 0b10111:
      //drive(64,256);
      setMotorA(64);
      setMotorB(256);
      break;
    //left 3 & 4
    case 0b00111:
    case 0b01111:
      //drive(32,196);
      setMotorA(32);
      setMotorB(128);
      break;  
    //right 1
    case 0b11001:
      //drive(256,196);
      setMotorA(256);
      setMotorB(128);
      break;
    //right 2
    case 0b11101:
      //drive(256,64);
      setMotorA(255);
      setMotorB(64);
      break;
    //right 3 & 4
    case 0b11100:
    case 0b11110:
      //drive(196,32);
      setMotorA(128);
      setMotorB(32);
      break;
    //any other state
    case 0b10000:
    case 0b00001:
    case 0b00000:
      tickCounter = 0;
      setMotorA(192);
      setMotorB(192);
      break;
    case 0b01011:
    case 0b01001:
    case 0b00011:
      setMotorA(0);
      setMotorB(0);
      delay(100);
      tickCounter++;
      if(tickCounter > 5) {
        Timer.timerStart();
        nextState = LAP;
      }
      break;
    default:
      //drive(192,192);
      tickCounter = 0;
      setMotorA(192);
      setMotorB(192);
      break;
  }
}

void handleLap() {
  //normal control logic
  //when tick is crossed, next State is set to FINISH and stopwatch is ended
  //when lineState == 0b11111 for more than a certain number of loops, transition to LOST state
  lineState = getLineState();
  switch(lineState) {
    //center
    case 0b11011:
      setMotorA(192);
      setMotorB(192);
      break;
    //left 1
    case 0b10011:
      //drive(196,256);
      setMotorA(128);
      setMotorB(256);
      break;
    //left 2
    case 0b10111:
      //drive(64,256);
      setMotorA(64);
      setMotorB(256);
      break;
    //left 3 & 4
    case 0b00111:
    case 0b01111:
      //drive(32,196);
      setMotorA(32);
      setMotorB(128);
      break;  
    //right 1
    case 0b11001:
      //drive(256,196);
      setMotorA(256);
      setMotorB(128);
      break;
    //right 2
    case 0b11101:
      //drive(256,64);
      setMotorA(255);
      setMotorB(64);
      break;
    //right 3 & 4
    case 0b11100:
    case 0b11110:
      //drive(196,32);
      setMotorA(128);
      setMotorB(32);
      break;
    //any other state
    case 0b10000:
    case 0b00001:
    case 0b00000:
      tickCounter = 0;
      setMotorA(192);
      setMotorB(192);
      break;
    case 0b01011:
    case 0b01001:
    case 0b00011:
      setMotorA(0);
      setMotorB(0);
      delay(100);
      tickCounter++;
      if(tickCounter > 5) {
        lapTime = timer.timerLap()
        nextState = FINISH;
      }
      break;
    case 0b11111:
      lostCounter++;
      if(lostCounter > 5) {
        lostCounter = 0;
        nextState = LOST;
      }
    default:
      //drive(192,192);
      tickCounter = 0;
      setMotorA(192);
      setMotorB(192);
      break;
  }
}

void handleLost() {
  lineState = getLineState();
  if (lineState == 0b11111) {
    setMotorA(-255);
    setMotorB(-255);
  }
  else {
    nextState = LAP;
  }
}

void handleFinish() {
  setMotorA(0);
  setMotorB(0);
  displayStrings("Lap Time (s):", to_string(lapTime))
  if(!digitalRead(BUTTON)) { //if the button is pressed
    while (digitalRead(BUTTON)) { //wait for the button to become unpressed
      delay(10); //wait 10 ms between checks to reduce CPU usage
    }
    nextState = RESET;
  }
}

//main loop function
void loop() {
  //state cases
  switch (currentState) {
    case RESET:
      handleReset();
      break;
    case COUNTDOWN:
      handleCountdown();
      break;
    case RUNUP:
      handleRunup();
      break;
    case LAP:
      handleLost();
      break;
    case LOST:
      handleLost();
      break;
    case FINISH:
      handleFinish();
      break;
  }
  //state switcher
  if(nextState != currentState) {
    stateCounter = 0;
    currentState = nextState;
  }
  //short delay
  delay(5);
}




/*
  lineState = getLineState();
  Serial.print(uint8ToBinary(lineState) + "\n");
  Serial.print((digitalRead(BUTTON) == HIGH) + "\n");
  Serial.print(running + "\n");
  if(running) {
    switch(lineState) {
      //center
      case 0b11011:
        setMotorA(192);
        setMotorB(192);
        break;
      //left 1
      case 0b10011:
        //drive(196,256);
        setMotorA(128);
        setMotorB(256);
        break;
      //left 2
      case 0b10111:
        //drive(64,256);
        setMotorA(64);
        setMotorB(256);
        break;
      //left 3 & 4
      case 0b00111:
      case 0b01111:
        //drive(32,196);
        setMotorA(32);
        setMotorB(128);
        break;  
      //right 1
      case 0b11001:
        //drive(256,196);
        setMotorA(256);
        setMotorB(128);
        break;
      //right 2
      case 0b11101:
        //drive(256,64);
        setMotorA(255);
        setMotorB(64);
        break;
      //right 3 & 4
      case 0b11100:
      case 0b11110:
        //drive(196,32);
        setMotorA(128);
        setMotorB(32);
        break;
      //any other state
      case 0b10000:
      case 0b00001:
      case 0b00000:
        tickCounter = 0;
        setMotorA(192);
        setMotorB(192);
        break;
      case 0b01011:
      case 0b01001:
      case 0b00011:
        setMotorA(0);
        setMotorB(0);
        delay(100);
        tickCounter++;
        if(tickCounter > 5) {
          setMotorA(255);
          setMotorB(0);
          delay(10000);
        }
        break;
      default:
        //drive(192,192);
        setMotorA(192);
        setMotorB(192);
        break;
    }
  }
  else {
    //drive(0,0);
    setMotorA(0);
    setMotorB(0);
  }
  if (!digitalRead(BUTTON)) {
    running = !running;
    delay(250);
  }
  //delay(5);
*/