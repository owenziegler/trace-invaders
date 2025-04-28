/*
module_driver.h

Joel Osho & Owen Ziegler
3/19/2025

Description:
Header file for motor driver code, contains declaration of all motor driver functions
*/
#ifndef MODULE_DRIVER_H
#define MODULE_DRIVER_H

/*

*/
void driverSetup();

void setMotorA(int speed);
void setMotorB(int speed);

void drive(int left, int right);

void left();

void right();

void reverse();

void nudgeleft();

void nudgeright();

#endif
