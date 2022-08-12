/*******************************************************************************
   Converter for Half-width kana
   (Japanese, Katakana)

   Define your own converter for handling of half width Katakana characters 
   
   When you comnpare the UTF-8 character set you will see following differences to the HD44870 A00 ROM:
   
   The ROM misses the first halfwidth symbol and starts with 
   
   ｡  ef bd a1  HALFWIDTH IDEOGRAPHIC FULL STOP
   ｢  ef bd a2  HALFWIDTH LEFT CORNER BRACKET
   ｣  ef bd a3  HALFWIDTH RIGHT CORNER BRACKET
   ､  ef bd a4  HALFWIDTH IDEOGRAPHIC COMMA
   
   then halfwidth kana starts with
   ･  ef bd a5  HALFWIDTH KATAKANA MIDDLE DOT
   to
   ｿ  ef bd bf  HALFWIDTH KATAKANA LETTER SO

   Then there is an offset and it starts again at
   ﾀ  ef be 80  HALFWIDTH KATAKANA LETTER TA
   to
   ﾟ  ef be 9f  HALFWIDTH KATAKANA SEMI-VOICED SOUND MARK   
   
   Important: You have to chose the proper hardware interface in the sketch!

   by noiasca
   2020-09-17 
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
#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, cbConverter);  // create lcd object parallel 4bit

//#include <NoiascaHW/lcd_i2c.h>         // I2C
//LiquidCrystal_I2C lcd(addr, cols, rows, cbConverter);       // create lcd object I2C

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
    if (special == 0xEF)                         // check if the first byte fits
    {
      special = special << 8;                    // leftshift existing value
      special = special + value;                 // and add current value to special
    }
    else if (special >= 0xEF00)                  // check if we had already two bytes
    {
      if (value >= 0x80 && value <= 0x9F)        // Kana in UTF8 is not consecutive - there is an used area between 0xEFBDBF and 0xEFBE80 - but the HD44870 is consecutive
       value += 0x40;
      special = 0;                               // delete special for next usage
      outputMode = PRINT;                        // we have a printable character in value
    }
  }
  else                                           // print 1 byte character
  {
    outputMode = PRINT;
  }
  return outputMode;                             // return if printable or not
}

void setup()
{
  Serial.begin(115200);
  //  SPI.begin();                     // start the SPI bus - uncomment if needed for the display
  //  Wire.begin();                    // start the I2C bus - uncomment if needed for the display

  lcd.begin();                         // initialize the lcd
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("A･ｦｧｨｩｪBｰｱｲｳCﾀﾁﾂ");        // Hankaku kana
  lcd.setCursor(0, 1);
  lcd.print("DﾃﾐﾑﾒEﾜﾝﾞﾟ!"); 
}

void loop()
{}
