/*******************************************************************************
   Convert Norwegian
   Norwegian Characters for standard HD44780 LCD

   call the converter_custom to use up to 8 special characters for your language
   including UTF-8 two byte characters

   Important: You have to chose the proper hardware interface in the sketch!

   by noiasca
   2021-02-27 OK (4590/345)

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
//const byte bl = 10;                            // set to 255 if not used
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_custom);  // create lcd object parallel 4bit

#include <NoiascaHW/lcd_i2c.h>                   // I2C
LiquidCrystal_I2C lcd(0x27, cols, rows, convert_custom);           // create lcd object I2C most common addresses are 0x3F or 0x27

//#include <NoiascaHW/lcd_spi.h>                 // SPI
//LiquidCrystal_SPI lcd(0x40, cols, rows, csPin, convert_custom);  // create lcd object SPI

// you need one function which prepares the custom characters and map them to the UTF-8 code:
void customCharacterMapping_no()
{
  //  This UTF8 code will become  -->   that custom character
  utf8_to_customChar[0] = 0xC385;    lcd.createChar_P(0, latin_capital_a_ring_above);    // Å  
  utf8_to_customChar[1] = 0xC386;    lcd.createChar_P(1, latin_small_a_ring_above);      // å                                    
  utf8_to_customChar[2] = 0xC392;    lcd.createChar_P(2, latin_capital_ae);              // Æ
  utf8_to_customChar[3] = 0xC398;    lcd.createChar_P(3, latin_small_ae);                // æ
  utf8_to_customChar[4] = 0xC3A5;    lcd.createChar_P(4, latin_capital_o_stroke);        // Ø
  utf8_to_customChar[5] = 0xC3A6;    lcd.createChar_P(5, latin_small_o_stroke);          // ø
  utf8_to_customChar[6] = 0xC3B8;    lcd.createChar_P(6, latin_capital_o_grave);         // Ò
  utf8_to_customChar[7] = 0xC3B2;    lcd.createChar_P(7, latin_small_o_grave);           // ò      
}


void setup()
{
  // SPI.begin();                      // start the SPI bus - activate if needed for the display
  Wire.begin();                        // start the I2C bus - activate if needed for the display

  lcd.begin();                         // initialize the lcd
  lcd.backlight();
  customCharacterMapping_no();

  lcd.setCursor(0, 0);
  lcd.print("god morgen: -3°C");
  lcd.setCursor(0, 1);
  lcd.print("Å å Æ æ Ø ø Ò ò");
}

void loop()
{}
