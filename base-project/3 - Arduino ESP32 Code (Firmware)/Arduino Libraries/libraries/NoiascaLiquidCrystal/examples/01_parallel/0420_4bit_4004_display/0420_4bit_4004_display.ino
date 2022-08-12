/*******************************************************************************
   LCD 4 bit Mode 40x04 display
   LCD in parallel 4 bit mode

   Hardware:
   this is for 40x04 LCD, consisting of basically two displays, hence the two enable lines
   LCD should be wired as follows:

   LCD          UNO
   --------------------------
   VSS   GND    GND
   VDD   5V     5V
   V0           -   contrast - connect a poti to GND, around 2K7
   RS           P8  RS
   RW    GND    -   Read/Write not used in this library - must be pulled down to GND !(!!!)
   E            P9  Enable 1
   E2           P11 Enable 2
   D0           -   not used in 4bit mode
   D1           -   not used in 4bit mode
   D2           -   not used in 4bit mode
   D3           -   not used in 4bit mode
   D4           P4  DB4
   D5           P5  DB5
   D6           P6  DB6
   D7           P7  DB7
   LEDA   5V
   LEDK   GND   P10 Backlight circuitry (HIGH signal enables backlight using a simple NPN transistor)
   
   by noiasca
   2021-04-05 Base 4bit 2124/201
   
*******************************************************************************/

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit

const byte cols = 40;                  // 40 columns/characters per row (must be correct for the 40x4)
const byte rows = 4;                   //  4 rows
const byte rs = 8;                     // RS pin
const byte rw = 255;                   // RW pin is not used, therefore you must set it to 255
const byte en = 9;                     // enable pin for first IC (upper rows)
const byte en2 = 11;                   // enable pin for second IC (lower rows)
const byte d4 = 4;                     // data pin
const byte d5 = 5;                     // data pin
const byte d6 = 6;                     // data pin
const byte d7 = 7;                     // data pin 
const byte bl = 10;                    // set to 255 if not used
const t_backlightPol blType = POSITIVE;// set to either POSITIVE, NEGATIVE, FAULTY

LiquidCrystal_4bit lcd(rs, rw, en, en2, d4, d5, d6, d7, bl, blType, cols, rows);                   // set all 12 parameters
//LiquidCrystal_4bit lcd(rs, rw, en, en2, d4, d5, d6, d7, bl, blType, cols, rows, convert_small);  // a converter (Ä gets ä)
//LiquidCrystal_4bit_base lcd(rs, rw, en, en2, d4, d5, d6, d7, bl, blType, cols, rows);            // base class without UTF-8 support - only for testing

void setup()
{
  lcd.begin();                         // initialize the LCD
  //lcd.backlight();                     // turn on backlight
  lcd.setCursor(2, 0);
  lcd.print("Hello, world!  ");
  lcd.setCursor(0, 1);
  lcd.print("α β μ Σ ° ÷ ∞ ← → ä ö ü ß Ä Ö Ü");     // show some special character entered in UTF-8
  lcd.setCursor(0, 2);  
  lcd.print( ("123456789A123456789B123456789C123456789D"));
  lcd.setCursor(8, 3);
  lcd.print("noiasca liquid crystal 4004");
}

void loop()
{
/*
    delay(1000);
    lcd.setCursor(20, 0);
    lcd.print(millis()/1000);
    lcd.print("                ");
*/
}
