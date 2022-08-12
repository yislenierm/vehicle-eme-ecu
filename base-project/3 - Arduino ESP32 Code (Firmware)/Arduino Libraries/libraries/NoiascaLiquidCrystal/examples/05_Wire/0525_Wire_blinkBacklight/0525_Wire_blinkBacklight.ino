/* ******************************************************************************
   Blink backlight using the built in RGB chip

   Hardware:
   LCD with native Wire/I2C Interface
   Internal LCD Controller AIP31068L and a PCA9633 for the RGB backlight

   Variants:
   - Sureeno with RGB Chip at 0x60         Available here: https://s.click.aliexpress.com/e/_dXgx0kh
   - Grove (Seeed) with RGB Chip at 0x62   Available here: https://amzn.to/352Kblx

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
  lcd.backlight();                     // set the backlight brigthness to a medium value
  // Print a message to the LCD.
  lcd.print("blink backlight");
}

void loop() {
  lcd.blinkBacklight();
  lcd.setRGB(255, 255, 0);             // send RGB color to display: yellow
  lcd.setCursor(0, 1);
  lcd.print("start blink");
  delay(3000);                         // the display keeps blinking even if we have paused the 
  lcd.noBlinkBacklight();
  lcd.setRGB(0, 255, 0);               // send RGB color to display: green
  lcd.setCursor(0, 1);
  lcd.print("stop blink ");
  delay(2000);                         // dirty delay
}
