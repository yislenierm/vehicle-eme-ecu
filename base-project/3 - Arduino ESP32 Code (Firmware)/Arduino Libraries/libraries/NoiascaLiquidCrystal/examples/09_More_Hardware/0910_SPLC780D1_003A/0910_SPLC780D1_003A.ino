/*******************************************************************************
   Convert Characters for European Languages

   Hardware:
   - this sketch requests a LCD with SPLC780D1 and 003A ROM (displays with HD44780 will not show correctly)

   Important: You have to chose the proper hardware interface in the sketch!

   needs about 320 Byte more flash than a HD44780, but has a lot more special characters

   by noiasca
   2020-12-20

 *******************************************************************************/
#include <NoiascaLiquidCrystal.h>      // download library from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows

// activate the needed lines according to your LCD hardware

/*
  // this is for parallel interface 4bit
  #include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
  const byte rs = 8;
  //const byte rw = 255;                 // set to 255 if not used - for future use
  const byte en = 9;
  const byte d4 = 4;
  const byte d5 = 5;
  const byte d6 = 6;
  const byte d7 = 7;
  const byte bl = 10;                    // set to 255 if not used
  LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, convert_SPLC780D1_003A);  // create lcd object parallel 4bit
*/

/*
  // this is for I2C expander
  #include <NoiascaHW/lcd_i2c.h>         // I2C
  const byte addr = 0x3F;                // set the LCD address for I2C to 0x3F or 0x27
  LiquidCrystal_I2C lcd(addr, cols, rows, convert_SPLC780D1_003A);       // create lcd object I2C
*/

// this is for SPI expander
#include <NoiascaHW/lcd_spi.h>        // SPI
const byte csPin = 10;
LiquidCrystal_SPI lcd(0x40, cols, rows, csPin, convert_SPLC780D1_003A);  // create lcd object SPI

const uint32_t interval = 3000;

// the structure of the content information
struct Content
{
  const char lang[3];    // iso language code
  const char *output1;   // just a sentence to be displayed
  const char *output2;   // special characters used in that language (as far as I found them on wikipedia)
};

// Demo content to be printed on the LCD
Content content[] = {
  {"ca", "Arduino capità", "ÀàÇçÈèÉéÍíÏïÒòÓóÚúÜü"}, // Catalan              // partially substituted
  {"cs", "Dobrý večer",    "áčďéěíňóřšťúůýž"},      // Czech                // partially substituted
  {"de", "Grüß Euch", "Ä ä Ö ö Ü ü ß"},             // German               // Greek beta used for sharp s
  {"dk", "god aften", "Æ æ Ø ø Å å"},               // Danish               // full
  {"en", "money rules", "£ ¢ Ææäëïöü"},             // English              // partially substituted
  {"es", "El español es muy fácil, ¿verdad?", "ÁáÉéÍíÑñÓóÚúÜü¡¿ Çç ªº"},    // partially substituted
  {"et", "Estonia", "Ää Öö Üü Õõ"},                 // Estnish              // partially substituted
  {"fr", "bon jour",     "ÀÂÆÇÈÉÊËÎÏÔŒÙÛÜŸ"},       // French               // partially substituted
  {"fr", "Français 2/2", "àâæçèéêëîïôœùûüÿ"},                               // partially substituted
  {"hu", "Helló. Jó reggelt", "ÁáÉéÓóÖöŐÚúÜüŰű"},   // Hungarian            // partially substituted
  {"it", "Arrivederci", "Àà ÈèÉé Òò Ùù"},           // Italian              // partially substituted
  {"it", "ciao 2/2",    "àé è ìíî òó ùú"},                                  // full
  {"sv", "Hallå", "Å å Ä ä Ö ö"},                   // Swedish              // full
  {"sk", "Dobré ráno", "áäčďéíĺľňóôŕšťúýž"},        // Slovakian            // partially substituted
  {"sl", "Dobro jutro", "č š ž Č Š Ž"},             // Slovenian            // all characters substituted
  {"sq", "Albania", "Ç ç Ë ë"},                     // Albanian             // partially substituted
  {"no", "god morgen", "Å å Æ æ Ø ø Ò ò"},          // Norwegian            // partially substituted
  {"pt", "Olá",     "àáâãçéêíóôõú"},                // Portuguese           // partially substituted
  {"pt", "Olá 2/2", "ÀÁÂÃÇÉÊÍÓÔÕÚ"},                                        // partially substituted
  {"po", "cześć", "ĄĆĘŁŃÓŚŹŻ"},                     // Polish               // all characters substituted
  {"ro", "bună seara", "ă â î ș ț"}                 // Romanian             // partially substituted
};

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
  lcd.setCursor(0, 0);
  lcd.print(F("ISO8859 Latin1-4"));
  lcd.setCursor(0, 1);
  lcd.print(F("ÄäÖöÜüß éÆ°µ→"));
}

void setup()
{
  Serial.begin(115200);
  SPI.begin();                      // start the SPI bus - activate if needed for the display
  // Wire.begin();                     // start the I2C bus - activate if needed for the display

  lcd.begin();                         // initialize the lcd
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SPLC780D1 003A");
  lcd.setCursor(0, 1);
  lcd.print("ÅåÄäÖöÜüßµ~");
  delay(interval);
  showLatin();
  delay(interval);
  Serial.println(F("press Enter (Linefeed) to scroll through different languages"));
}

void loop()
{
  doDemo();
}
