/*******************************************************************************
   Convert for 3rd Party LCD Library

   This example shows how the use the build in UTF-8 converter from NoiascaLiquidCrystal
   for other (3rd party) LCD libraries.
   So if you need to use another LCD library but you want to use the UTF-8 support,
   use this pattern. For this example I'm using the "original" Liquid Crystal I2C.

   libraries
   - NoiascaLiquidCrystal.h    (this library)
   - LiquidCrystal_I2C         by Frank de Brabander, 1.1.2

   by noiasca
   2021-02-03  (compilies with warnings from the 3rd party lib)
 *******************************************************************************/

#include <NoiascaLiquidCrystal.h>                // download from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm

#include <Wire.h>
#include <LiquidCrystal_I2C.h>                   // include the 3rd party library
// you need to modify the file "LiquidCrystal_I2C.h"
// around row 110 you will find the access specifier "private:" 
// change it to "protected:"

const byte cols = 16;                            // columns/characters per row
const byte rows = 2;                             // how many rows
const byte addr = 0x3F;                          // set the LCD address for I2C to 0x3F or 0x27

// now lets create a very specific lcd object to be used with the 3rd party libray
// the new class will inherit all variables and methods from the 3rd party library.
// It will be the parent class - and will be enriched with one variable and a modified method

class MyLCD : public LiquidCrystal_I2C           // MyLCD shoud inherit from 3rd party class
{
  protected:
    uint32_t special = 0;                        // buffer to store incomming special characters

  public :
    MyLCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) :
      LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows),            // the default constructor must call the constructor of the parent class
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
      //Serial.print (F("MyLCD write ")); Serial.println(value, HEX);
      switch (funcPtr (special, value))
      {
        case NOPRINT :        // don't print
          break;
        case PRINT2 :         // print from second pattern. Only available for ST7070 devices
          blink();
          send(value, Rs);    // check the included library, which low level method is used to write a value. In case of the  LiquidCrystal_I2C it is send(value, Rs); 
          noBlink();
          break;
        case ADDE :           // print an additional e after character
          send(value, Rs);
          send('e', Rs);
          break;
        default :             // includes PRINT: just print
          send(value, Rs);
      }
      return (1); // we always assume success (either print to display or store to special character
    }
};

MyLCD lcd(addr, cols, rows);     // now create the LCD object based on the new class

void setup()
{
  lcd.init();                    // initialize the lcd
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("German - Grüß Gott");
  lcd.setCursor(0, 1);
  lcd.print("Ä ä Ö ö Ü ü ß");
}

void loop()
{}
