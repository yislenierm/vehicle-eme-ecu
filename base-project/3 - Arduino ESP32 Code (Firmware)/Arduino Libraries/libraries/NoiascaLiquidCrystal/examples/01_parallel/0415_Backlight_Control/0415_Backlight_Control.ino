/*******************************************************
  Backlight Control

  If backlight control is not working as intended try this workaround.
  It will define a local class with modified backlight control.

  If backlight is working but inversed change the name of the methods.

  by noiasca
  Version 2021-02-03

********************************************************/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte rs = 8;                     // RS pin
const byte en = 9;                     // EN pin
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 3;                     // backlight pin, PWM pins are 3, 5, 6, 9, 10 and 11

#include <NoiascaLiquidCrystal.h>      // download from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm
#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit

class MyLCD_4bit : public LiquidCrystal_4bit {
  public:
    MyLCD_4bit(uint8_t rsPin, uint8_t enPin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, uint8_t blPin, uint8_t lcd_cols, uint8_t lcd_rows) :
      LiquidCrystal_4bit(rsPin, enPin, d4Pin, d5Pin, d6Pin, d7Pin, blPin, lcd_cols, lcd_rows)
    {}

    void noBacklight() {
      digitalWrite(blPin, LOW);
    }

    void backlight() {
      digitalWrite(blPin, HIGH);
    }

    void setBacklight(uint8_t new_val) {  // Set the backlight brightness (0-255) 
      analogWrite(blPin, new_val);
    }
};

MyLCD_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);  // create lcd object for your new class

void setup()
{
  lcd.begin();                         // initialize the LCD
  pinMode(bl, OUTPUT);                 // set your backlight pin to OUTPUT
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Backlight Control");
  lcd.setCursor(0, 1);
  lcd.print("αβμΣ°÷∞←→äöüßÄÖÜ");     // show some special character entered in UTF-8
}

void loop()
{
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Backlight off   ");
  lcd.noBacklight();
  delay(500);
  
  lcd.setCursor(0, 1);
  lcd.print("Backlight on    ");
  lcd.backlight();
  delay(1000);

  byte rnd = random(256);
  lcd.setBacklight(rnd);
  lcd.setCursor(0, 1);
  lcd.print("Backlight "); lcd.print(rnd);
}
