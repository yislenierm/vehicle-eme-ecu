/*******************************************************************************
   Convert Characters

   Define your own converter for handling of special characters
   including UTF-8 two byte characters

   Important: You have to chose the proper hardware interface in the sketch!

   by noiasca
   2020-09-04
 *******************************************************************************/
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x3F;                // set the LCD address for I2C to 0x3F or 0x27
const byte rs = 8;
//const byte rw = 255;                 // set to 255 if not used - for future use
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // set to 255 if not used

// Prototype (the callback function will be defined later)
uint8_t cbConverter (uint32_t &special, uint8_t &value);

// activate the needed lines according to your LCD hardware
//#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, cbConverter);  // create lcd object parallel 4bit

#include <NoiascaHW/lcd_i2c.h>         // I2C
LiquidCrystal_I2C lcd(addr, cols, rows, cbConverter);       // create lcd object I2C

//#include <NoiascaHW/lcd_spi.h>        // SPI
//LiquidCrystal_SPI lcd(0x40, cols, rows, csPin, cbConverter);  // create lcd object SPI

// this example callback converter mapps UTF-8 characters into custom characters
uint8_t cbConverter (uint32_t &special, uint8_t &value)
{
  uint8_t outputMode = NOPRINT;                  // assume not printable character
  if ((value & 0b11000000) == 0b11000000)        // if we receive a UTF8 multi byte character, it will be indicated in the two MSB of the first byte
  {
    special = value;                             // just store the byte as special character for the next call
  }
  else if (special > 0)                          // if there is a special character stored
  {
    if (special == 0xC3)                         // check if the first byte fits
    {
      if (value == 0x84) value = 5;              // map value based on the second byte to another character in the ROM. 0 - 7 are the custom characters
      else if (value == 0x96) value = 6;
      else if (value == 0x9c) value = 7;
    }
    special = 0;                                 // reset special (in any cas)
    outputMode = PRINT;                          // we have a printable character in value
  }
  else                                           // print in any case
  {
    if (value == 92) value = 3;                  // remap the back slash to custom character
    else if (value == 126) value = 4;            // remap the tilde to custom character
    outputMode = PRINT;
  }
  return outputMode;                             // return if printable or not
}

// define some custom characters to be loaded into the LCD
const uint8_t backslash[8] = {0b00000, 0b10000, 0b01000, 0b00100, 0b00010, 0b00001, 0b00000, 0b00000}; // the backslash
const uint8_t tilde[8] =     {0b00000, 0b00000, 0b01000, 0b10101, 0b00010, 0b00000, 0b00000, 0b00000}; // a tilde
const uint8_t AE[8] =        {0b10001, 0b01110, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b00000}; // German Ä
const uint8_t OE[8] =        {0b10001, 0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 0b00000}; // German Ö
const uint8_t UE[8] =        {0b10001, 0b00000, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 0b00000}; // German Ü

void setup()
{
  Serial.begin(115200);
  //  SPI.begin();                     // start the SPI bus - uncomment if needed for the display
  Wire.begin();                        // start the I2C bus - uncomment if needed for the display

  lcd.begin();                         // initialize the lcd
  lcd.backlight();

  lcd.createChar(4, tilde);            // create a cumstom character, the assigned number has to fit to your cbConverter
  lcd.createChar(3, backslash);
  lcd.createChar(5, AE);
  lcd.createChar(6, OE);
  lcd.createChar(7, UE);

  lcd.setCursor(0, 0);
  lcd.print("Convert chars");
  lcd.setCursor(0, 1);
  lcd.print("\\ ~ Ä E I Ö Ü");      // backslash must be escaped
}

void loop()
{}
