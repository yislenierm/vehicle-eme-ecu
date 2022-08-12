/* ******************************************************************************
   Fade backlight brightness using the setBacklight() method
   
   Hardware:
   LCD with native Wire/I2C Interface
   Internal LCD Controller AIP31068L and a PCA9633 for the RGB backlight

   Variants:
   - Sureeno with RGB Chip at 0x60         Available here: https://s.click.aliexpress.com/e/_dXgx0kh
   - Grove (Seeed) with RGB Chip at 0x62   Available here: https://amzn.to/352Kblx

   Credits: 
   This program is based on ideas of the example Fade.ino from [DFRobot](http://www.dfrobot.com), 2016

   by noiasca
   2020-09-05
****************************************************************************** */

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte lcdAddr = 0x3E;             // set the LCD address to 0x3E
//const byte rgbAddr = 0x60;             // you can set the rgbAddr of the (Sureeno defaults internally to 0x60, use 0x62 for Grove displays);

#include <Wire.h>
#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_wire.h>        // include the proper HW interface
LiquidCrystal_Wire_RGB lcd(lcdAddr, cols, rows);           // create lcd object for a Sureeno RGB display
//LiquidCrystal_Wire_RGB lcd(lcdAddr, rgbAddr, cols, rows);    // create lcd object for a Grove display

void fadeBacklight() {
  for (byte i = 0; i < 255; i++) {
    lcd.setBacklight(i);
    delay(5);
  }
  delay(500);
  for (byte i = 254; i > 0; i--) {
    lcd.setBacklight(i);
    delay(5);
  }
  delay(500);
}

void setup() {
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  // Print a message to the LCD.
  lcd.print("fade demo");

  byte red = 255;                      // set each color 0..255
  byte green = 127;
  byte blue = 0;
  lcd.setRGB(red, green, blue);        // send RGB color to display
  lcd.setBacklight(127);               // set the backlight brigthness to a medium value
}

void loop() {
  fadeBacklight();
  lcd.setCursor(0, 1);
  lcd.print("Green");
  lcd.setRGB(0, 255, 0);
  fadeBacklight();
  lcd.setCursor(0, 1);
  lcd.print("Blue ");
  lcd.setRGB(0, 0, 255);
  fadeBacklight();
  lcd.setCursor(0, 1);
  lcd.print("Red ");
  lcd.setRGB(255, 0, 0);
}
