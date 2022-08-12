/* ******************************************************************************
   Hello World Wire/I2C Interface

   Hardware:
   LCD with native Wire/I2C Interface
   Internal LCD Controller AIP31068L and a PCA9633 for the RGB backlight

   Variants:
   - Sureeno with RGB Chip at 0x60         Available here: https://s.click.aliexpress.com/e/_dXgx0kh
   - Grove (Seeed) with RGB Chip at 0x62   Available here: https://amzn.to/352Kblx

   Important:
   I highly recommend to run an I2C scanner to identify the correct I2C addresses! 
   The Sureeno display will show 3 addresses in the I2C scanner:
   0x3E the AIP31068L display driver itself
   0x60 the RGB driver PCA9633 
   0x03 from the reserved address area - also the PCA9633

   open tasks:
   - ISO 8583 Latin 1 - 4  Characters on LCD with SPI connector

   Hardware:
   LCD like Sureeno or Grove

   by noiasca
   2020-09-05

 ****************************************************************************** */

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte lcdAddr = 0x3E;             // set the LCD address to 0x3E
//const byte rgbAddr = 0x60;             // you can set the rgbAddr of the (Sureeno defaults internally to 0x60, use 0x62 for Grove displays

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
  //lcd.blinkBacklight();                // blink the backlight (done by the display, needs no resources from Arduino
  //lcd.noBlinkBacklight();              // stop blinking backlight
  //lcd.setBacklight(64);                // set brightness of backlight (0-255) 
  lcd.print("A random color");
}

void loop()
{
  byte r = random(255);           // get random color
  byte g = random(255);
  byte b = random(255);
  lcd.setRGB(r, g, b);            // set the display color
  lcd.setCursor(0, 1);
  lcd.print("0x");                // display the color in hex code
  if (r < 0x10) lcd.print("0");
  lcd.print(r, HEX);
  if (g < 0x10) lcd.print("0");
  lcd.print(g, HEX);
  if (b < 0x10) lcd.print("0");
  lcd.print(b, HEX);
  lcd.print(" ");
  lcd.print(millis() / 1000);
  lcd.print("s");
  delay(2000);                    // dirty delay
}
