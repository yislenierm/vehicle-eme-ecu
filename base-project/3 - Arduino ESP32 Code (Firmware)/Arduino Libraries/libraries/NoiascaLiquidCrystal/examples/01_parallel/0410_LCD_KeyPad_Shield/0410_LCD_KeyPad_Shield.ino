/*******************************************************
  LCD KeyPad Shield

  This is an example sketch a LCD KeyPad Shield
  with 4 buttons connected to ADC 0.

  My shield has following silk print on the PCB:
    DFROBOT
    Drive the Future

  credits:
    There can be found various variants of this sketch in the web, 
    I don't remember the "real" owner.
    This sketch has some adoptions for the new Noiasca LCD Library.

  Version 
    2021-01-08 ok (4190/261)

********************************************************/

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte rs = 8;                     // RS pin
const byte en = 9;                     // EN pin
const byte d4 = 4;
const byte d5 = 5;
const byte d6 = 6;
const byte d7 = 7;
const byte bl = 10;                    // backlight pin

#include <NoiascaLiquidCrystal.h>      // download from https://werner.rothschopf.net/202009_arduino_liquid_crystal_intro.htm
#include <NoiascaHW/lcd_4bit.h>        // parallel interface, 4bit
LiquidCrystal_4bit lcd(rs, en, d4, d5, d6, d7, bl, cols, rows);  // create lcd object

enum {btnRIGHT, btnUP, btnDOWN, btnLEFT, btnSELECT, btnNONE};

// define some values used by the panel and buttons
byte lcd_key    = 0;  // the pressed button
int adc_key_in  = 0;  // the readed ADC value
int adc_old     = 0;  // the previous ADC value

// read the buttons
byte read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  Serial.println(adc_key_in);
  // my buttons when readed are centered at these values: 0,  99, 254, 407, 639
  // we add approx 50 to those values and check if we are close
  if (adc_key_in > 1000) return btnNONE;   // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;                           // when all others fail, return this...
}

const byte arrowUp[8] = {0b00000, 0b00100, 0b01110, 0b10101, 0b00100, 0b00100, 0b00100, 0b00000};
const byte arrowDown[8] = {0b00000, 0b00100, 0b00100, 0b00100, 0b10101, 0b01110, 0b00100, 0b00000};

void setup()
{
  Serial.begin(115200);
  lcd.begin();                         // start the display
  lcd.backlight();
  lcd.createChar(5, arrowUp);
  lcd.createChar(6, arrowDown);
  lcd.setCursor(0, 0);
  lcd.print(F("LCD KeyPad Shield "));  // print a simple message
}

void loop()
{
  lcd_key = read_LCD_buttons();  // read the buttons
  if (adc_old / 4 != adc_key_in / 4) // only print the new value, if different to the old one - avoids flickerin of LCD
  {
    lcd.setCursor(7, 1);
    if (adc_key_in < 1000) lcd.print(" ");
    if (adc_key_in < 100) lcd.print(" ");
    if (adc_key_in < 10) lcd.print(" ");
    lcd.print(adc_key_in);
    adc_old = adc_key_in;
  }
  lcd.setCursor(12, 1);
  lcd.print(millis() / 1000);    // display seconds elapsed since power-up
  lcd.setCursor(0, 1);
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
      {
        lcd.print(F("RIGHT →"));
        break;
      }
    case btnLEFT:
      {
        lcd.print(F("LEFT  ←"));
        break;
      }
    case btnUP:
      {
        lcd.print(F("UP    \x5"));
        break;
      }
    case btnDOWN:
      {
        lcd.print(F("DOWN  \x6"));
        break;
      }
    case btnSELECT:
      {
        lcd.print(F("SELECT "));
        break;
      }
    case btnNONE:
      {
        lcd.print(F("NONE   "));
        break;
      }
  }
}
