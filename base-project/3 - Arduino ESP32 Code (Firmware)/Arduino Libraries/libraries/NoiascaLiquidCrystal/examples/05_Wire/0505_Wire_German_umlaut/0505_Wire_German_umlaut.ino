/* ******************************************************************************
   Individual Converter 
   example how to use different UTF8 converter variants from the library
   
   Hardware:
   LCD with native Wire/I2C Interface
   Internal LCD Controller AIP31068L and a PCA9633 for the RGB backlight

   Variants:
   - Sureeno with RGB Chip at 0x60         Available here: https://s.click.aliexpress.com/e/_dXgx0kh
   - Grove (Seeed) with RGB Chip at 0x62   Available here: https://amzn.to/352Kblx

   Important:
   I highly recommend to run an I2C scanner to identify the correct I2C addresses!

   LCD like Sureeno or Grove

   by noiasca
   2020-09-07

 ****************************************************************************** */

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte lcdAddr = 0x3E;             // set the LCD address to 0x3E
//const byte rgbAddr = 0x60;             // you can set the rgbAddr of the (Sureeno defaults internally to 0x60, use 0x62 for Grove displays);
const uint32_t interval = 2000;

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_wire.h>        // include the proper HW interface

LiquidCrystal_Wire_RGB lcd(lcdAddr, cols, rows);                   // use the standard converter (Ä gets converted to A) from library
//LiquidCrystal_Wire_RGB lcd(lcdAddr, cols, rows, convert_dummy);    // a dummy converter from library which does nothing
//LiquidCrystal_Wire_RGB lcd(lcdAddr, cols, rows, convert_ae);       // a converter (Ä gets converted to Ae) from library
//LiquidCrystal_Wire_RGB lcd(lcdAddr, cols, rows, convert_small);    // a converter (Ä gets converted to ä) from library
//LiquidCrystal_Wire_RGB lcd(lcdAddr, cols, rows, convert_special);  // a converter (Ä gets converted to ä) from library - not ready yet

void setup()
{
  Serial.begin(115200);
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight 
  //lcd.createUml();                   // create 3 German Umlauts using Special Characters 5, 6, and 7 - used for convert_special
  lcd.setCursor(2, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ä Ö Ü ä ö ü ß");
}

void loop()
{}
