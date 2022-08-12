/* ******************************************************************************
   Set Color by Serial Monitor
   send color by color and close the line only with carriage return

   Hardware:
   LCD with native Wire/I2C Interface
   Internal LCD Controller AIP31068L and a PCA9633 for the RGB backlight

   Variants:
   - Sureeno with RGB Chip at 0x60         Available here: https://s.click.aliexpress.com/e/_dXgx0kh
   - Grove (Seeed) with RGB Chip at 0x62   Available here: https://amzn.to/352Kblx

   by noiasca
   2020-09-04

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

const byte dtaSize = 5;                // size for read data buffer
char dtaUart[dtaSize];                 // read data buffer
byte dtaLen = 0;                       // a counter

byte color[] {255, 127, 127};          // we need three colors
byte actualColor = 2;                  // ... and a start value for actual

void setup() {
  Serial.begin(115200);
  Wire.begin();                        // start I2C library
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  lcd.print("set color");
  lcd.setCursor(0, 1);
  lcd.print("in serial monitor");
  changeColor();
}

void changeColor()                               // change color and ask for next color
{
  color[actualColor] = (byte)atoi(dtaUart);      // converts the number in ascii into a real number
  lcd.setRGB(color[0], color[1], color[2]);
  Serial.print("actual red=");                   // print the actual used colors
  Serial.print(color[0]);
  Serial.print("\t green=");
  Serial.print(color[1]);
  Serial.print("\t blue=");
  Serial.println(color[2]);
  actualColor++;                                 // next color
  if (actualColor > 2) actualColor = 0;          // care about wrap around 0 - 1 - 2 - 0
  Serial.print("Enter new color for ");
  switch (actualColor)
  {
    case 0: Serial.print("red"); break;
    case 1: Serial.print("green"); break;
    default: Serial.print("blue");
  }
  Serial.println();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 10 || c == 13 || dtaLen >= dtaSize - 1)
    {
      dtaUart[dtaLen++] = '\0';         // close the input
      changeColor();                    
      dtaLen = 0;                       // reset value for next run
    }
    else if (c >= ' ')
    {
      dtaUart[dtaLen++] = c;            // add character to read buffer
    }
  }
}
