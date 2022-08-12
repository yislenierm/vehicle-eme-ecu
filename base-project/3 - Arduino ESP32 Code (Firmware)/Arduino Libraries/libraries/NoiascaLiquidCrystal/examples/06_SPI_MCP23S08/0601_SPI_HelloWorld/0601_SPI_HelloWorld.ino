/*******************************************************************************
   Hello World 
   LCD & SPI
   
   LCD with MCP23S08 - 8-Bit I/O Expander with Serial Interface (SPI)
   As the MCP23S08 only offers 8 pins and we need RS RW EN - only 4bit mode can be used.
   the remaining pin (P3) will be used for backlight control.

   Supports some ISO 8583 Latin 1 - 4  characters on LCD with SPI connector

   Hardware:
   MCP23S08 and LCD should be wired as follows:
   
   LCD    MCP     UNO
   --------------------------
   VSS    GND     GND
   VDD    Vin     5V
   V0     -       -     contrast - connect a poti to GND
   RS     P0 RS   -
   RW     P1 RW   -
   E      P2 EN   -
   DB0    -       -
   DB1    -       -
   DB2    -       -
   DB3    -       -
   D4     P4 DB4  -
   D5     P5 DB5  -
   D6     P6 DB6  -
   D7     P7 DB7  -
   LEDA   GND     -            uses P3 for backlight circuitry (HIGH signal enables backlight using a simple NPN transistor)
   LEDK   5V      5V      
   -      RES     -            must be pulled up to high
   -      A0      -            pull down (GND)
   -      A1      -            pull down (GND)
   -      CS      D10 SS       or another free pin for slave select (chip select)
   -      SO      D12 MISO
   -      SI      D11 MOSI
   -      SCL     D13 SCL    
   
   by noiasca
   2021-04-05     base 2044/80
   2020-older     base 2026/117
                  base 1848/111 (best) 

 *******************************************************************************/

#include <NoiascaLiquidCrystal.h>      // use the adopted library downloaded from https://werner.rothschopf.net/202003_arduino_liquid_crystal_umlaute.htm  
#include <NoiascaHW/lcd_spi.h>         // include the proper IO interface

const byte cols = 16;                  // columns/characters per row
const byte rows = 2;                   // how many rows
const byte addr = 0x40;                // though SPI, the MCP23S08 has two additional adress pins. Use 0x40 if A0 and A1 are connected to GND
const byte csPin = 10;                 // the CS PIN for the MCP23S08 IC
const uint32_t interval = 1000;

LiquidCrystal_SPI lcd(addr, cols, rows, csPin);          // create lcd object - with support of special characters
//LiquidCrystal_SPI_base lcd(addr, cols, rows, csPin);   // create lcd object - base clase, if you don't need characters > 127 or if you are low on memory

void setup()
{
  SPI.begin();                         // start SPI
  lcd.begin();                         // initialize the LCD
  lcd.backlight();                     // turn on backlight
  lcd.setCursor(3, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(5, 1);
  lcd.print("Arduino");
  if (rows > 2)
  {
    lcd.setCursor(0, 2);
    lcd.print("Noiasca LC SPI 2020");
    lcd.setCursor(2, 3);
    lcd.print("Powered by noiasca");
  }
}

void loop()
{

/*
  delay(interval);
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  lcd.print("                ");
*/
  
/*
  // Blink test to check basic SPI communication
  static byte i;
  i++;
  lcd.setBacklight(i%2);
*/
}
