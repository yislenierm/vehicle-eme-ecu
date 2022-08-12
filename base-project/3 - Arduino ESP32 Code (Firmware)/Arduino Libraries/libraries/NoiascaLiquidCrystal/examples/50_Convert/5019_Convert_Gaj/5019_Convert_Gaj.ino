/*******************************************************************************
   Convert Gaj's Latin Alphabet
   Gaj's Latin Alphabet on standard HD44780 LCD

   call the converter_custom to use up to 8 special characters for languages using Gaj's Alphabet
   including UTF-8 two byte characters

   Important: You have to chose the proper hardware interface in the sketch!

   by noiasca
   2021-02-16 OK (4582 / 349)
 *******************************************************************************/
#include <NoiascaLiquidCrystal.h>                // download library from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm
#include <utility/NoiascaCustomCharacters.h>     // file with several predefined custom characters

const byte cols = 16;                            // columns/characters per row
const byte rows = 2;                             // how many rows

// activate the needed lines according to your LCD hardware
//#include <NoiascaHW/lcd_4bit.h>                // parallel interface, 4bit
//const byte rs = 8;
//const byte en = 9;
//const byte d4 = 4;
//const byte d5 = 5;
//const byte d6 = 6;
//const byte d7 = 7;
//const byte bl = 10;                  // set to 255 if not used
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_custom);  // create lcd object parallel 4bit

#include <NoiascaHW/lcd_i2c.h>         // I2C
LiquidCrystal_I2C lcd(0x27, cols, rows, convert_custom);           // create lcd object I2C most common addresses are 0x3F or 0x27

//#include <NoiascaHW/lcd_spi.h>       // SPI
//LiquidCrystal_SPI lcd(0x40, cols, rows, csPin, convert_custom);  // create lcd object SPI

void customCharacterMapping_gaj()
{
  //  This UTF8 code will become  -->   that custom character
  utf8_to_customChar[0] = 0xC48C;    lcd.createChar_P(0, latin_capital_c_caron);         // Č
  utf8_to_customChar[1] = 0xC48D;    lcd.createChar_P(1, latin_small_c_caron);           // č                                    
  utf8_to_customChar[2] = 0xC490;    lcd.createChar_P(2, latin_capital_d_stroke);        // Đ
  utf8_to_customChar[3] = 0xC491;    lcd.createChar_P(3, latin_small_d_stroke);          // đ
  utf8_to_customChar[4] = 0xC5A0;    lcd.createChar_P(4, latin_capital_s_caron);         // Š 
  utf8_to_customChar[5] = 0xC5A1;    lcd.createChar_P(5, latin_small_s_caron);           // š
  utf8_to_customChar[6] = 0xC5BD;    lcd.createChar_P(6, latin_capital_z_caron);         // Ž
  utf8_to_customChar[7] = 0xC5BE;    lcd.createChar_P(7, latin_small_z_caron);           // ž       
}

void setup()
{
  // SPI.begin();                      // start the SPI bus - activate if needed for the display
  Wire.begin();                        // start the I2C bus - activate if needed for the display

  lcd.begin();                         // initialize the lcd
  lcd.backlight();

  customCharacterMapping_gaj();

  lcd.setCursor(0, 0);
  lcd.print("Gaj's Latin alphabet");
  lcd.setCursor(0, 1);
  lcd.print("Č č Đ đ Š š Ž ž");
}

void loop()
{}
