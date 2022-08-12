/*******************************************************************************
   Convert Danish
   Danish Characters on standard HD44780 LCD

   Define your own converter for handling of special characters
   including UTF-8 two byte characters

   Important: You have to chose the proper hardware interface in the sketch!

   by noiasca
   2021-02-27 ok   4502 / 341
 *******************************************************************************/
#include <NoiascaLiquidCrystal.h>                // download library from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm
#include <utility/NoiascaCustomCharacters.h>     // file with several predefined custom characters

const byte cols = 16;                            // columns/characters per row
const byte rows = 2;                             // how many rows
const byte addr = 0x27;                          // set the LCD address for I2C to 0x3F or 0x27
const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                              // set to 255 if not used

// activate the needed lines according to your LCD hardware
//#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_custom);  // create lcd object parallel 4bit

#include <NoiascaHW/lcd_i2c.h>         // I2C
LiquidCrystal_I2C lcd(addr, cols, rows, convert_custom);       // create lcd object I2C

//#include <NoiascaHW/lcd_spi.h>       // SPI
//LiquidCrystal_SPI lcd(0x40, cols, rows, csPin, convert_custom);  // create lcd object SPI


// you need one function which prepares the custom characters and map them to the UTF-8 code:
void customCharacterMapping_dk()
{
  //  This UTF8 code will become  -->   that custom character
  utf8_to_customChar[2] = 0xC385;    lcd.createChar_P(2, latin_capital_a_ring_above);    // Å 0xC385
  utf8_to_customChar[3] = 0xC3A5;    lcd.createChar_P(3, latin_small_a_ring_above);      // å 0xC3A5
  utf8_to_customChar[4] = 0xC386;    lcd.createChar_P(4, latin_capital_ae);              // Æ 0xC386
  utf8_to_customChar[5] = 0xC3A6;    lcd.createChar_P(5, latin_small_ae);                // æ 0xC3A6
  utf8_to_customChar[6] = 0xC398;    lcd.createChar_P(6, latin_capital_o_stroke);        // Ø 0xC398
  utf8_to_customChar[7] = 0xC3B8;    lcd.createChar_P(7, latin_small_o_stroke);          // ø 0xC3B8
}

void setup()
{
  // SPI.begin();                      // start the SPI bus - activate if needed for the display
  Wire.begin();                        // start the I2C bus - activate if needed for the display

  lcd.begin();                         // initialize the lcd
  lcd.backlight();
  customCharacterMapping_dk();         // call your character mapping

  lcd.setCursor(0, 0);
  lcd.print("god aften -3°C");
  lcd.setCursor(0, 1);
  lcd.print("Å å Æ æ Ø ø dk");
}

void loop()
{}
