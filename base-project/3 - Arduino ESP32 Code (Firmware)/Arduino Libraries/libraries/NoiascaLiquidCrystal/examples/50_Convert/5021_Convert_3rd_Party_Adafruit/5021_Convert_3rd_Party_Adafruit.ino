/*******************************************************************************
   Convert for 3rd Party LCD Library

   This example shows how the use the build in UTF-8 converter from NoiascaLiquidCrystal
   for other (3rd party) LCD libraries.
   So if you need to use another LCD library but you want to use the UTF-8 support,
   use this pattern. For this example I'm using the Adafruit LCD Library.

   libraries
   - NoiascaLiquidCrystal.h    (this library)
   - Adafruit_LiquidCrystal.h  by Adafruit
   by noiasca
   2021-02-03  OK (with patched Adafruit Library)
 *******************************************************************************/

#include <NoiascaLiquidCrystal.h>                // download from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm

#include <Wire.h>
#include "Adafruit_LiquidCrystal.h"              // include the 3rd party library
// you need to modify the file "Adafruit_LiquidCrystal.h"
// around row 252 you will find the access specifier "private:" 
// change it to "protected:"

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;

// now lets create a very specific lcd object to be used with the 3rd party libray
// the new class will inherit all variables and methods from the 3rd party library.
// It will be the parent class - and will be enriched with one variable and a modified method

class MyLCD : public Adafruit_LiquidCrystal      // MyLCD shoud inherit from 3rd party class
{
  protected:
    uint32_t special = 0;                        // buffer to store incomming special characters

  public :
    MyLCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1,uint8_t d2, uint8_t d3) :
      Adafruit_LiquidCrystal(rs, enable, d0, d1, d2, d3),            // the default constructor must call the constructor of the parent class
      funcPtr(convert)              // function pointer to default converter
    {}                              // MyLCD constructor calls the 3rd party constructor

    using CallBack = uint8_t (*)(uint32_t &special, uint8_t &value);
    CallBack funcPtr;

    // next we need an adoption of the write() method
    // write() - process data character byte to lcd
    // it returns number of bytes successfully PROCESSED. Either printed to the device or stored to special
    // i.e. 1 if success or 0 if no character was processed (error)
    size_t write(uint8_t value)
    {
      switch (funcPtr (special, value))
      {
        case NOPRINT :        // don't print
          break;
        case PRINT2 :         // print from second pattern. Only available for ST7070 devices
          blink();
          send(value, HIGH);
          noBlink();
          break;
        case ADDE :           // print an additional e after character
          send(value, HIGH);
          send('e', HIGH);
          break;
        default :             // includes PRINT: just print
          send(value, HIGH);
      }
      return (1); // we always assume success (either print to display or store to special character
    }
};

MyLCD lcd(rs, en, d4, d5, d6, d7);     // now create the LCD object based on the new class

void setup()
{
  lcd.begin(cols, rows);               // initialize the lcd
  lcd.setCursor(0, 0);
  lcd.print("German - Grüß Gott");
  lcd.setCursor(0, 1);
  lcd.print("Ä ä Ö ö Ü ü ß°");
}

void loop()
{}
