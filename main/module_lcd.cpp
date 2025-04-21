/*
module_lcd.cpp

Owen Ziegler
20250421

Description:
Implementation for LCD module. Contains definitions of all LCD module functions.
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "module_lcd.h"

#define SDA 4
#define SCL 5
#define LCD_ADDRESS 0x27
#define COLS 16
#define ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, COLS, ROWS);

void lcdSetup() {
  Wire.begin(SDA,SCL);
  lcd.init();
  lcd.backlight();
}

void displayStrings(String line1, String line2) {
  //check for valid input
  if(line1.length() > 16 || line2.length() > 16) {
    errorMessage();
  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line1);
    lcd.setCursor(0,1);
    lcd.print(line2);
  }
}

void displayError() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Error");
  lcd.setCursor(0,1);
  lcd.print("Invalid Input");
}
