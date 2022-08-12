/*
   UTF-8 save characters for LC-Displays with ROM Code A00

   it prints
   German Umlaut  ä ö ü
   Special characters like ° (degree), ~ (tilde), √ (sqare root), ∝, ∞ (infinity),  ← (arrow) → (arrow), ¥ Yen and £ Pound
   Some special characters from Greek like α β ε π μ ρ Σ used for Mathematic

   by noiasca

   2020-09-02
*/

const byte cols = 20;                  // columns/characters per row
const byte rows = 4;                   // how many rows
const byte rs = 8;
//const byte rw = 255;                 // set to 255 if not used - for future use
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // set to 255 if not used
const byte addr = 0x3F; 

const uint32_t interval = 3000;

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm

//#include <NoiascaHW/lcd_4bit.h>      // parallel interface, 4bit
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);      // use the standard converter (Ä gets converted to A)

#include <NoiascaHW/lcd_i2c.h>           // I2C Expander
LiquidCrystal_I2C lcd(addr, cols, rows); // set the LCD address to 0x27 (or 0x3F) for a 16 chars and 2 line display


void setup()
{
  Serial.begin(115200);
  //Wire.begin();                      // based on the used display, activate the Wire or SPI if necessary
  lcd.begin();                          // initialize the lcd
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(0, 0);                 // set cursor to start position

  showLatin();
  showSymbols();
  showGreek();

  lcd.print("ä");                      // print a single character
  lcd.print("→");                      // print a special character
}

void loop()
{
  greetings();
  allChars();
}

void showLatin()
{
  Serial.println(F("show Latin characters - German umlauts ä ö ü and ß"));
  String row0 = "AaOoUus latin";
  String row1 = "ÄäÖöÜüß";
  lcd.print(row0);
  lcd.setCursor(0, 1);
  lcd.print(row1);
  delay(interval);
}

void showGreek()
{
  Serial.println(F("show Greek characters"));
  lcd.clear();
  String row0 = "abepmrS greek";
  String row1 = "αβεπμρΣ";
  lcd.print(row0);
  lcd.setCursor(0, 1);
  lcd.print(row1);
  delay(5000);
}

void showSymbols()
{
  Serial.println(F("show special characters"));
  lcd.clear();
  String row0 = "DDmnPYTSPILRB";
  String row1 = "°÷·ñ£¥~√∝∞←→\\";
  lcd.print(row0);
  lcd.setCursor(0, 1);
  lcd.print(row1);
  delay(interval);
}

void greetings()
{
  Serial.println(F("send greetings from my country"));
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Hällau - Grüße"));  // Hello - greetings
  lcd.setCursor(0, 1);
  lcd.print(F("aus Österreich"));  // from Austria
  delay(interval);
}

void allChars()
{
  Serial.println(F("show special characters 0xA0 - 0xFF"));
  lcd.clear();
  for (int i = 0xA0; i <= 255; i++)
  {
    lcd.setCursor(0, 0);
    lcd.print("Char 0x         ");
    lcd.setCursor(7, 0);
    Serial.print(" 0x"); Serial.println(i, HEX);
    lcd.print(i, HEX);
    lcd.setCursor(10, 0);
    lcd.writeOld(i);  // if you need to write special characters in your code, use .writeOld
    delay(1000);
  }
  Serial.println();
}
