/*******************************************************************************
  CustomChars
  NoiascaLiquidCrystal_I2C

  This is a demo Sketch to show how to define custom characters including capital German umlauts

  name=CustomChars
  version=1.0.2
  author=noiasca

  Sketch Version 2021-02-13 ok
 *******************************************************************************/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte rs = 8;
//const byte rw = 255;                 // set to 255 if not used - for future use
const byte en = 9;
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // set to 255 if not used

#include <NoiascaLiquidCrystal.h>         // download library from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm
#include <NoiascaHW/lcd_i2c.h>
LiquidCrystal_I2C lcd(0x27, cols, rows);  // set the LCD address, mostly 0x27 (or 0x3F) for a 16 chars and 2 line display

//#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
//LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);  // create lcd object

const uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
const uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
const uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
const uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
const uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
const uint8_t check[8] = {0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0};
const uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
const uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

const uint8_t AE[8] = {0b10001, 0b01110, 0b10001, 0b10001, 0b11111, 0b10001, 0b10001, 0b00000}; // German Ä
const uint8_t OE[8] = {0b10001, 0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 0b00000}; // German Ö
const uint8_t UE[8] = {0b10001, 0b00000, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 0b00000}; // German Ü


void setup()
{
  Wire.begin();                      // start the I2C bus (if you compile for a I2C display)
  lcd.begin();                       // initialize the lcd
  lcd.backlight();

  lcd.createChar(0, bell);           // create the character
  lcd.createChar(1, note);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, duck);
  lcd.createChar(5, check);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);

  lcd.clear();
  lcd.print("Hello world...");
  lcd.setCursor(0, 1);
  for (byte i = 0; i < 8; i++)
  {
    lcd.write(i);
    lcd.print(" ");
  }
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Using createChar");
  lcd.createChar(5, AE);
  lcd.createChar(6, OE);
  lcd.createChar(7, UE);

  lcd.setCursor(0, 1);
  lcd.print("ä ");
  lcd.write(5);
  lcd.print(" ö ");
  lcd.write(6);
  lcd.print(" ü ");
  lcd.writeOld(7);

  delay(5000);
  displayKeyCodes();
}

// display all keycodes
void displayKeyCodes(void) {
  uint8_t i = 0;
  while (1) {
    lcd.clear();
    lcd.print("Codes 0x"); lcd.print(i, HEX);
    lcd.print("-0x"); lcd.print(i + 16, HEX);
    lcd.setCursor(0, 1);
    for (int j = 0; j < 16; j++) {
      lcd.writeOld(i + j);
    }
    i += 16;
    delay(4000);
  }
}

void loop()
{}
