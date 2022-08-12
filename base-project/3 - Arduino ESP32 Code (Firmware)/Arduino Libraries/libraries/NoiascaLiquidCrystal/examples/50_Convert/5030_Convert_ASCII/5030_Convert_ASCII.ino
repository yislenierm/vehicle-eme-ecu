/*
   Convert UTF8 characters to plain ASCII characters
   5030_Convert_ASCII
   
   For some languages with lot of diacritical marks (acute, grave, breve...) it might be needed to 
   map characters to their plain ASCII (lower 7bit ANSI) counterpart to make the text readable on LCD with HD44780 or AIP31068
   Example:
   Ê will get E
   
   You can switch through the examples by pressing enter in the serial monitor.

   This example is for Latin letters. If you need Cyrillic please see the example 5035_Convert_Cyrillic

   by noiasca
   2021-02-14 OK
*/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte csPin = 10;                 // the CS PIN for the MCP23S08 IC
const byte addr = 0x27;                // set the LCD address mostly 0x3F or 0x27, check with a I2C Scanner the correct address
const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // set to 255 if not used
const uint32_t interval = 1000;

#include <NoiascaLiquidCrystal.h>        // download from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 

//activate exact ONE converter
#define MYCONVERT convert_ASCII            // complete UTF8 to ASCII replacement (for all languages)
//#define MYCONVERT convert_gmw            // west germanic (German, English, Dutch, Scottish, Western Frisian)
//#define MYCONVERT convert_gmq            // North Germanic (Dansk, Swedish, Norwegian
//#define MYCONVERT convert_roa            // Romance (Catalan, Spanish, French, Italian, Portuguese, Romanian, (but also for Albanian, Estonian)
//#define MYCONVERT convert_sla            // Slavic: Czech, Slowakian, Slovenian, Polish
//#define MYCONVERT convert_hu             // Hungarian
//#define MYCONVERT convert_fi             // Finnish
//#define MYCONVERT convert_dummy          // empty implementation for test purpose

#include <NoiascaHW/lcd_4bit.h>                          // parallel interface, 4bit
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);  // create lcd object
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, MYCONVERT);  // create lcd object with special converter

#include <NoiascaHW/lcd_i2c.h>                           // I2C PCF Adapter
LiquidCrystal_I2C lcd(addr, cols, rows, MYCONVERT);      // create LCD object
//LiquidCrystal_I2C_ST7070 lcd(addr, cols, rows, MYCONVERT); // variant for ST7070 LCD

//#include <NoiascaHW/lcd_wire.h>                          // include the proper IO interface
//LiquidCrystal_Wire_RGB lcd(0x3E, cols, rows, MYCONVERT); // create lcd object

//#include <NoiascaHW/lcd_spi.h>                           // SPI MCP23S08 Adapter
//LiquidCrystal_SPI lcd(0x40, cols, rows, csPin);          // create lcd object  - with special characters

//LiquidCrystal_dummy lcd(addr, cols, rows);               // dummy (empty) object

// the structure of the content information
struct Content
{
  const char lang[3];    // iso language code
  const char *output1;   // just a sentence to be displayed
  const char *output2;   // special characters used in that language (as far as I found them on wikipedia)
};

// Demo content to be printed on the LCD
Content content[] = {
  // West Germanic - gmw
  {"de", "Grüß Euch", "Ä ä Ö ö Ü ü ß"},             // German - Deutsch
  {"en", "money rules", "dep:Ææäëïöü"},             // English
  // Nord Germanic - gmq
  {"dk", "god aften", "Å å Æ æ Ø ø"},               // Danish - dansk
  {"is", "Icelandic", "ÁáÐðÉéÍíÓóÚúÝýÞþÆæÖö"},      // Icelandic - íslenska https://en.wikipedia.org/wiki/Icelandic_language#Writing_system
  {"sv", "Hallå", "Å å Ä ä Ö ö"},                   // Swedish - svenska
  {"no", "god morgen", "Å å Æ æ Ø ø Ò ò"},          // Norwegian - Norsk
  // Slavic - sla
  {"cs", "Dobrý večer", "áčďéěíňóřšťúůýž"},         // Czech - čeština
  {"sk", "Dobré ráno", "áäčďéíĺľňóôŕšťúýž"},        // Slovak - Slovenčina 
  {"sl", "Dobro jutro", "Č č Š š Ž ž"},             // Slovene - Slovenski jezik
  {"pl", "cześć", "ĄĆĘŁŃÓŚŹŻ"},                     // Polish - polski
  {"99", "Gaj's Latin alphabet", "Č č Đ đ Š š Ž ž"},// Serbo Croatian Languages - Gaj's Latin alphabet https://en.wikipedia.org/wiki/Gaj%27s_Latin_alphabet
  // Romance - roa
  {"ca", "Arduino capità", "ÀàÇçÈèÉéÍíÏïÒòÓóÚúÜü"}, // Catalan - català
  {"es", "El español es muy fácil, ¿verdad?", "¡¿ÁáÉéÍíÑñÓóÚúÜü Çç ªº"}, // Spanish 
  {"et", "Estonian", "Ä ä Ö ö Ü ü Õ õ"},            // Estonian - eesti - uralic but works best in Romance
  {"fr", "bon jour", "ÀÂÆÇÈÉÊËÎÏÔŒÙÛÜŸ"},           // French - français
  {"fr", "bon jour", "àâæçèéêëîïôœùûüÿ"},           // French - français
  {"it", "Arrivederci", "ÀàÈèÉéÒòÙù"},              // Italian - l'italiano
  {"it", "variante", "àéèìíîòóùú"},                 // Italian - l'italiano
  {"pt", "Olá", "àáâãçéêíóôõú"},                    // Portuguese - Português
  {"pt", "Olá", "ÀÁÂÃÇÉÊÍÓÔÕÚ"},                    // Portuguese - Português
  {"ro", "bună seara", "ă â î ș ț"},                // Romanian - Română
  {"sq", "Albanian", "Ç ç Ë ë"},                    // Albanian - Shqip - use Romance
  // other
  {"fi", "suomi", "Åå Ää Öö Šš Žž"},                // Finnish - suomi
  {"hu", "Helló. Jó reggelt", "ÁÉÓÖŐÚÜŰáéóöőúüű"}   // Hungarian - magyar
};

void setup()
{
  Serial.begin(115200);
  Serial.println(F("+++++++++++++++"));

  //SPI.begin();                          // start SPI if needed
  //Wire.begin();                         // start the I2C/Wire Library if needed

  lcd.begin();                         // initialize the lcd
  lcd.backlight();                     // turn on backlight
  //lcd.initRGB();
  //lcd.setRGB(255, 255, 0);

  lcd.setCursor(0, 0);                   // set cursor to start position
  showLatin();
  delay(interval);
  //showLanguage(7); // fr
  //delay(interval);
}

void loop()
{
  doDemo();
}

void doDemo()
{
  //for (auto &current : content)
  static byte i = 0;

  if (Serial.available() > 0)
  {
    Serial.read();
    Serial.println(content[i].lang);
    lcd.clear();
    lcd.print(content[i].lang);
    lcd.print(": ");
    lcd.print(content[i].output1);
    lcd.setCursor(0, 1);
    lcd.print(content[i].output2);
    //delay(interval);
    i++;
    i = i % (sizeof(content) / sizeof(content[0]));
  }
}

void showLatin()
{
  //lcd.setRGB(128, 64, 0); delay(2);
  Serial.println(F("show Latin characters"));
  const char* row0 = "ISO8859 Latin1-4";
  const char* row1 = "ÄäÖöÜüß µ→";
  lcd.setCursor(0, 0); delay(2);
  lcd.print(row0);
  lcd.setCursor(0, 1); delay(2);
  lcd.print(row1);
  delay(interval);
}

// example print one specific language
void showLanguage(size_t i) 
{
  Serial.println(content[i].lang);
  lcd.clear();
  lcd.print(content[i].lang);
  lcd.print(": ");
  lcd.print(content[i].output1);
  lcd.setCursor(0, 1);
  lcd.print(content[i].output2);
  //delay(interval);
}
