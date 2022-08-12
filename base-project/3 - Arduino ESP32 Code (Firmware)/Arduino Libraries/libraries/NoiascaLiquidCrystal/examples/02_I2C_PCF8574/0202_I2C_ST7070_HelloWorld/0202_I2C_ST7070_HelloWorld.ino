/*
   ISO 8583 Latin 1 - 4  Characters on the ST7070

   This sketch demonstrates the capabilities of the ST7070 LCD IC.
   It will show different Variants of latin letters used in European languages.
   Open the serial monitor in press Enter (LineFeed) to scroll through the examples

   ISO/IEC 8859-1, Latin-1, Westeuropäisch          https://de.wikipedia.org/wiki/ISO_8859-1
               -2  Latin-2, Mitteleuropäisch        https://de.wikipedia.org/wiki/ISO_8859-2
               -3  Latin-3, Südeuropäisch
               -4  Latin-4, Nordeuropäisch

   Important: The presentation of these special characters will not work with the HD44780 displays!

   Hardware:
   A ST7070 display with I2C PCF8574 LCD Backpack

   by noiasca
   2020-05-12
*/

const byte cols = 20;                  // columns/characters per row
const byte rows = 4;                   // how many rows
const byte addr = 0x3F;                // set the LCD address to 0x27 or 0x3F for a 16 chars and 2 line display
const uint32_t interval = 3000;

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm
#include <NoiascaHW/lcd_i2c.h>         // include the proper IO interface

// The standard constructor handles Latin-1 only:
//LiquidCrystal_I2C_ST7070 lcd(addr, cols, rows);       // this is for displays with ST7070 driver, it has additional character support

// The extended constructor handles additional characters from Latin-2, Latin-3 and Latin-4
LiquidCrystal_I2C_ST7070_Ext lcd(addr, cols, rows);     // this is for displays with ST7070 driver with extended special character support

// the structure of the content information
struct Content
{
  const char lang[3];    // iso language code
  const char *output1;   // just a sentence to be displayed
  const char *output2;   // special characters used in that language (as far as I found them on wikipedia)
};

// Demo content to be printed on the LCD
Content content[] = {
  {"ca", "Arduino capità","ÀàÇçÈèÉéÍíÏïÒòÓóÚúÜü"}, // catalan
  {"cz", "Dobrý večer", "áčďéěíňóřšťúůýž"},
  {"de", "Grüß Euch", "Ä ä Ö ö Ü ü ß"},
  {"dk", "god aften", "Æ æ Ø ø Å å"},
  {"en", "money rules", "£ ¢ dep:Æ æ ä ë ï ö ü"},
  {"es", "El español es muy fácil, ¿verdad?", "¡¿ÁáÉéÍíÑñÓóÚúÜü Çç ªº"},
  {"et", "","Ää Öö Üü Õõ"}, // Estnisch
  {"fr", "bon jour", "ÀÂÆÇÈÉÊËÎÏÔŒÙÛÜŸ"},
  {"fr", "bon jour", "àâæçèéêëîïôœùûüÿ"},
  {"hu", "Helló. Jó reggelt", "Á É ÓÖŐ ÚÜŰ"},
  {"it", "Arrivederci", "Àà Èè Éé Òò Ùù"},
  {"it", "variante", "àéèìíîòóùú"},    // 
  {"se", "Hallå", "Å å Ä ä Ö ö"},
  {"sk", "Dobré ráno", "áäčďéíĺľňóôŕšťúýž"}, // dann stirbt das
  {"sl", "Dobro jutro", "č š ž Č Š Ž"},
  {"sq", "Albania", "Ç ç Ë ë"},              // Albanisch
  {"no", "god morgen", "Å å Æ æ Ø ø Ò ò"},
  {"pt", "Olá", "àáâãçéêíóôõú"},
  {"pt", "Olá", "ÀÁÂÃÇÉÊÍÓÔÕÚ"},
  {"po", "cześć", "ĄĆĘŁŃÓŚŹŻ"},
  {"ro", "bună seara", "ă â î ș ț"}
};

void setup()
{
  Serial.begin(115200);
  Wire.begin();                        // start the I2C/Wire Library
  lcd.init();                          // initialize the lcd
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(0, 0);                 // set cursor to start position

  showLatin();
  delay(interval);
  Serial.println(F("press Enter (Linefeed) to scroll through different languages"));
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
  Serial.println(F("show Latin characters"));
  const char* row0 = "ISO8859 Latin1-4";
  const char* row1 = "ÄäÖöÜüß ýč →";
  lcd.print(row0);
  lcd.setCursor(0, 1);
  lcd.print(row1);
  delay(interval);
}
