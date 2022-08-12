/*
   Support of Cyrillic characters on liquid crystal display
   5035_Convert_Cyrillic

   This sketch includes several LCD hardware:
   - Support LCDs with SPLC780D1 002A ROM (sold as "Russian") Cyrillic - https://s.click.aliexpress.com/e/_AdTdSO
   - Support LCDs with ST7070
   - Convert Cyrrillic UTF8 characters to plain ASCII characters (for the "standard" LCDs without Cyrillic characters)
   
   You can switch through the examples by pressing enter in the serial monitor.

   by noiasca
   2021-04-04 tested and OK
*/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte csPin = 10;                 // the CS PIN for the MCP23S08 IC
const byte addr = 0x27;                // set the I2C LCD address to 0x3F or 0x27
const byte rs = 8;
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // set to 255 if not used

#include <NoiascaLiquidCrystal.h>      // download from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm 

//activate exact ONE converter
#define MYCONVERT convert_SPLC780D1_002A                   // Cyrillic converter for SPLC780D1 002A ROM https://s.click.aliexpress.com/e/_AdTdSO
//#define MYCONVERT convert_ST7070_ext                     // Cyrillic converter for ST7070
//#define MYCONVERT convert_cyrillic_min                   // minimized converter Cyrillic to ASCII for LCD with standard character set


//#include <NoiascaHW/lcd_4bit.h>                          // parallel interface, 4bit
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows, MYCONVERT);  // create lcd object with special converter

#include <NoiascaHW/lcd_i2c.h>                           // I2C PCF Adapter
LiquidCrystal_I2C lcd(addr, cols, rows, MYCONVERT);      // create LCD object

//#include <NoiascaHW/lcd_wire.h>                          // include the proper IO interface
//LiquidCrystal_Wire_RGB lcd(0x3E, cols, rows, MYCONVERT); // create lcd object

//#include <NoiascaHW/lcd_spi.h>                           // SPI MCP23S08 Adapter
//LiquidCrystal_SPI lcd(0x40, cols, rows, csPin, MYCONVERT);  // create lcd object  - with special characters

// the structure of the content information
struct Content
{
  const char lang[3];    // iso language code
  const char *output1;   // just a sentence to be displayed
  const char *output2;   // special characters used in that language (as far as I found them on wikipedia)
};

// Demo content to be printed on the LCD
Content content[] = {
  {"ru", "Добрый день", "Аа Бб Вв Гг Дд"},          // Dobryy den' - hello
  {"ru", "доброе утро", "Ее Ёё Жж Зз Ии"},          // dobroye utro - good morning
  {"ru", "Добрый вечер", "Йй Кк Лл Мм Нн"},         // Dobryy vecher - good evening
  {"ua", "доброго вечора", "Оо Пп Рр Сс Тт"},       // dobroho vechora - good evening
  {"bu", "добър вечер", "Уу Фф Хх Цц Чч"},          // dobŭr vecher - good evening
  {"sb", "добро вече", "Шш Щщ Ъъ Ыы Ьь"},           // dobro veče - good evening  
  {"mz", "добро попладне", "Ээ Юю Яя"},             // dobro popladne - good evening
  {"z8", "Pre-1918 letters", "І і Ѳ ѳ Ѣ ѣ Ѵ ѵ"},    // // more cyrillic letters - FITA and IZHITSA replaced according GOST 
};

void setup()
{
  Serial.begin(115200);
  Serial.println(F("+++++++++++++++"));

  //SPI.begin();                       // start SPI if needed
  Wire.begin();                      // start the I2C/Wire Library if needed

  lcd.begin();                         // initialize the lcd
  lcd.backlight();                     // turn on backlight
  //lcd.initRGB();
  //lcd.setRGB(255, 255, 0);

  lcd.setCursor(0, 0);                   // set cursor to start position
  showBegin();
}

void loop()
{
  doDemo();
}

void doDemo()
{
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
    i++;
    i = i % (sizeof(content) / sizeof(content[0]));
  }
}

void showBegin()
{
  //lcd.setRGB(128, 64, 0); 
  Serial.println(F("convert cyrillic characters"));
  lcd.setCursor(0, 0);
  lcd.print("cyrillic & ASCII");
  lcd.setCursor(0, 1);
  lcd.print("Россия, Україна");
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
}
