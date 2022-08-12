/*
   Displays text sent over the serial port (e.g. from the Serial Monitor) on
   an attached LCD.
   YWROBOT
   Compatible with the Arduino IDE 1.0
   Library version:1.1

   Version 
   2020-12-21 
*/
// LCD Parameters
const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows

// set the hardware type
#define TYPE 1                         // 1 parallel 4bit, 2 I2C

#include <NoiascaLiquidCrystal.h>      // download from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 

#if TYPE == 1
const byte rs = 8;
//const byte rw = 255;                 // set to 255 if not used - for future use
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;
#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);  // create lcd object
#endif

#if TYPE == 2
const byte addr = 0x3F;                // most used LCD addresses are 0x3F or 0x27
#include <NoiascaHW/lcd_i2c.h>         // include the proper IO interface
LiquidCrystal_I2C lcd(addr, cols, rows);  // create lcd object - with support of special characters
#endif

void setup()
{
  Serial.begin(115200);
#if TYPE == 2
  Wire.begin();                         // activate your bus system
#endif
  lcd.begin();                          // initialize the lcd
  lcd.backlight();
}

void loop()
{
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}
