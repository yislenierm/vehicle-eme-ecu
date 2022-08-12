/*******************************************************************************
  ScrollTextLibrary
  NoiascaLiquidCrystal_I2C

  This is a demo Sketch to show how to scroll the LCD Display with the library method
  This demo is non-blocking - without any delay

  name=ScrollTextLibrary
  version=1.0.1
  author=noiasca

  Sketch Version 2020-09-04
 *******************************************************************************/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x3F;                // most used LCD address is 0x3F or 0x27

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_i2c.h>         // include the proper IO interface
LiquidCrystal_I2C lcd(addr, cols, rows);       // create lcd object - with support of special characters

void setup()
{
  Wire.begin();
  lcd.begin();                          // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("123456789ä123456789ö123456789ü123456789ß"); // the memory can store up to 40 characters per line
}

// this function will call the scrollDisplayLeft method in a specific period
void tickScroll()
{
  static uint32_t previousMillis = 0;
  const uint16_t interval = 300;
  if (millis() - previousMillis > interval)
  {
    lcd.scrollDisplayLeft();
    previousMillis = millis();
  }
}

void loop()
{
  tickScroll(); // call this function as often as possible in the loop
}
