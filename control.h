#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(I2C_LCD_ADDRESS); 

// button pins
#define B_LEFT  4
#define B_UP    6
#define B_DOWN  5
#define B_RIGHT 7
#define B_STOP  3
#define B_START 9
#define B_SW    8

void stop_button_push() {
  stopped = true;
  rpm_l = 0;
  rpm_r = 0;
}

void setupControl() {
  lcd.begin(20, 4);              // initialize the lcd
  lcd.setBacklight(255);         // turn on the backlight
  lcd.home ();                   // go home
   // buttons
  pinMode(B_LEFT,  INPUT_PULLUP);
  pinMode(B_UP,    INPUT_PULLUP);
  pinMode(B_DOWN,  INPUT_PULLUP);
  pinMode(B_RIGHT, INPUT_PULLUP);
  pinMode(B_STOP,  INPUT_PULLUP);
  pinMode(B_START, INPUT_PULLUP);
  pinMode(B_SW,    INPUT_PULLUP);

  // STOP
  attachInterrupt(digitalPinToInterrupt(B_STOP), stop_button_push, FALLING);

}


