/* ******************************************************************************
   Hello World Wire (I2C) Interface

   Harddware:
   LCD with native Wire I2C interface
   Internal LCD Controller AIP31068L and a PCA9633 for the RGB backlight
   
   Variants:
   - Sureeno with RGB Chip at 0x60         Available here: https://s.click.aliexpress.com/e/_dXgx0kh
   - Grove (Seeed) with RGB Chip at 0x62   Available here: https://amzn.to/352Kblx

   Important:
   I highly recommend to run an I2C scanner to identify the correct I2C addresses! 
   The Sureeno display will show 3 addresses:
   0x3E the AIP31068L display driver itself
   0x60 the RGB driver PCA9633 
   0x03 from the reserved address area - this is also the PCA9633

   Hardware:
   LCD like Sureeno or Grove

   by noiasca
   2020-09-05 base 3510/326

 ****************************************************************************** */

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte lcdAddr = 0x3E;             // set the LCD address to 0x3E
//const byte rgbAddr = 0x60;             // you can set the rgbAddr of the (Sureeno defaults internally to 0x60, use 0x62 for Grove displays
const uint32_t interval = 1000;

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <Wire.h>
#include <NoiascaHW/lcd_wire.h>        // include the proper HW interface
LiquidCrystal_Wire_RGB lcd(lcdAddr, cols, rows);               // create lcd object for a Sureeno RGB display
//LiquidCrystal_Wire_RGB lcd(lcdAddr, rgbAddr, cols, rows);    // create lcd object for a Grove display

void setup()
{
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");     // show some special character entered in UTF-8
  if (rows > 2)
  {
    lcd.setCursor(0, 2);
    lcd.print("Noiasca LC Wir 2020");
    lcd.setCursor(2, 3);
    lcd.print("Powered by noiasca");
  }
}

void loop()
{
  //delay(interval);
  //lcd.setCursor(0, 1);
  //lcd.print(random(100000));
}
