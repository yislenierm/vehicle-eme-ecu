/*******************************************************************************
   Convert Estonian
   Estonian Characters on a standard HD44780 LCD

   call the converter_custom to use up to 8 special characters for your language
   including UTF-8 two byte characters

   Important: You have to chose the proper hardware interface in the sketch!

   by noiasca
   2021-02-27 ok   (4470/351)  
   
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

// you need one function which prepares the custom characters and map them to the UTF-8 code:
void customCharacterMapping_et()
{
  //  This UTF8 code will become  -->   that custom character                                
  utf8_to_customChar[3] = 0xC384;    lcd.createChar_P(3, latin_capital_a_diareses);      // Ä  
  utf8_to_customChar[4] = 0xC396;    lcd.createChar_P(4, latin_capital_o_diareses);      // Ö
  utf8_to_customChar[5] = 0xC39C;    lcd.createChar_P(5, latin_capital_u_diareses);      // Ü
  utf8_to_customChar[6] = 0xC395;    lcd.createChar_P(6, latin_capital_o_tilde);         // Õ
  utf8_to_customChar[7] = 0xC3B5;    lcd.createChar_P(7, latin_small_o_tilde);           // õ       
}

void setup()
{
  // SPI.begin();                                // start the SPI bus - activate if needed for the display
  Wire.begin();                                  // start the I2C bus - activate if needed for the display

  lcd.begin();                                   // initialize the lcd
  lcd.backlight();
  customCharacterMapping_et();
  
  lcd.setCursor(0, 0);
  lcd.print("eesti - Estonian -3°C");
  lcd.setCursor(0, 1);
  lcd.print("Ä ä Ö ö Ü ü Õ õ");
}

void loop()
{}
