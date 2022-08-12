/*******************************************************************************
   Variants of German umlauts Ä Ö Ü
   LCD in parallel 4 bit Mode

   open tasks:
   - ISO 8583 Latin 1 - 4  Characters on LCD with SPI connector

   Hardware:
   LCD should be wired as follows:

   LCD          UNO
   --------------------------
   VSS    GND   GND
   VDD    5V    Vin
   V0           -       contrast - connect a poti to GND
   RS           P0 RS
   RW     GND   -       Read/Write not used in this library - Pulldown to GND     
   E            P2 EN
   DB0          -
   DB1          -
   DB2          -
   DB3          -
   D4           P4 DB4
   D5           P5 DB5
   D6           P6 DB6
   D7           P7 DB7
   LEDA   5V
   LEDK   GND   P10 Backlight circuitry (HIGH signal enables backlight using a simple NPN transistor)

   by noiasca
   2020-09-01

   // Base 4bit 2928/296 
 *******************************************************************************/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // set to 255 if not used

#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);                     // use the standard converter (Ä gets converted to A)
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_ae);         // a converter (Ä gets Ae)
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_small);      // a converter (Ä gets ä)
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_special);    // a converter (Ä gets Ä)

void setup()
{
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  //lcd.createUml();                     // create 3 German Umlauts using Special Characters 5, 6, and 7 - used for convert_special
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ä Ö Ü ä ö ü ß");
}

void loop()
{}
