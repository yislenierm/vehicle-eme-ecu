/*******************************************************************************
   Various Variants of German Umlauts
   
   LCD with PCF8574 - 8-Bit I/O Expander with I2C Interface

   open tasks: 
   - ISO 8583 Latin 1 - 4  Characters on LCD with SPI connector

   Hardware:
   LCD with PCF8574 Backpack should be wired as follows:
   
   LCD          PCF8574
   --------------------------
   VSS    GND   GND
   VDD    5V    Vin
   V0           -             contrast - connect a poti to GND
   RS           P0 RS
   RW           P1 RW
   E            P2 EN
   DB0          -
   DB1          -
   DB2          -
   DB3          -
   D4           P4 DB4
   D5           P5 DB5
   D6           P6 DB6
   D7           P7 DB7
   LEDA   GND   P3 Backlight circuitry (HIGH signal enables backlight using a simple NPN transistor)
   LEDK   5V

   by noiasca
   2020-09-04

 *******************************************************************************/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x3F;                // set the LCD address to 0x3F or 0x27

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_i2c.h>         // include the proper IO interface

// For the I2C Expander are several constructors prepared:

LiquidCrystal_I2C lcd(addr, cols, rows);         // converts Ä Ö Ü to capital letter A O U
//LiquidCrystal_I2C_Ae lcd(addr, cols, rows);      // converts Ä Ö Ü to Ae Oe Ue 
//LiquidCrystal_I2C_Small lcd(addr, cols, rows);   // converts Ä Ö Ü to small letter ä ö ü
//LiquidCrystal_I2C_Special lcd(addr, cols, rows); // prints Ä Ö Ü, also activate lcd.createUml() in setup!
//LiquidCrystal_I2C_base lcd(addr, cols, rows);    // base class, if you don't need characters > 127 or if you are low on memory

void setup()
{
  Serial.begin(115200);
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  //lcd.createUml();                     // needed for LiquidCrystal_I2C_Special only - custom characters 5, 6, 7 used for Ä Ö Ü

  lcd.backlight();                     // turn on backlight
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ä Ö Ü ä ö ü ß");
}

void loop()
{
  //delay(interval);
  //lcd.setCursor(0, 1);
  //lcd.print(random(100000));
}
