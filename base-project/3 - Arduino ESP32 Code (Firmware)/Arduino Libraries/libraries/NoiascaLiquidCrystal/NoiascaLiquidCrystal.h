/*
   Noiasca Liquid Crystal
   
   Based on the work of DFRobot
   
   Open topics
   - move variable _backlight to I2C and SPI only
   
   by noiasca
   2021-04-04 extended for 4004
   2021-02-27 release candidate 1.2.3
   2021-02-16 createChar_P to load custom characters from PROGMEM
   2021-02-15 reorganised converter files (deleted converters from this file, deleted mapping to this file)
   2021-02-14 replaced ANSI by ASCII (kept ANSI as alias)
   2021-02-12 Cyrillic converter, SPLC780D1_002A Cyrillic
   2021-01-08 changed access specifier (release candidate 1.2.2)
   2020-12-20 optional normalization of UTF-8 characters
   2020-10-11 more Latin characters for SPLC780D1
   2020-10-06 SPLC780D1_003A European (release candidate 1.2.0)
*/

#pragma once
#ifndef NoiascaLiquidCrystal_h
#define NoiascaLiquidCrystal_h
#include <Arduino.h>

//#define DEBUG    // activates debug messages

#ifdef DEBUG
#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
#define DEBUG_PRINTLN(x)
#endif

#define NOIASCA_LIQUIDCRYSTAL_VERSION "NoiascaLiquidCrystal_1.2.4"   // this library
#define LIQUIDCRYSTAL_I2C_VERSION NOIASCA_LIQUIDCRYSTAL_VERSION      // backward compatibility

#include <inttypes.h>
#include "Print.h"
//Wire.h or SPI.h will be included in the respective display type .h

#include <utility/NoiascaUTF8.h>                 // contains the plain UTF8 to ASCII mapping
#include <utility/NoiascaConverter.h>            // all converters
#include <utility/NoiascaCustomCharacters.h>     // some predefined custom characters

// commands
#define LCD_CLEARDISPLAY 0x01                    // no further bit to set
#define LCD_RETURNHOME 0x02                      // no further bit defined
#define LCD_ENTRYMODESET 0x04                
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode                  // 0x04  compared to datasheet AIP31068
#define LCD_ENTRYLEFT 0x02                       // I/D   Increment Mode
#define LCD_ENTRYRIGHT 0x00                      // I/D   Decrement Mode
#define LCD_ENTRYSHIFTINCREMENT 0x01             // S     Shift
#define LCD_ENTRYSHIFTDECREMENT 0x00             // S     
                                                 
// flags for display on/off control              // 0x08
#define LCD_DISPLAYON 0x04                       // D   display on
#define LCD_DISPLAYOFF 0x00                      
#define LCD_CURSORON 0x02                        // C   cursor on
#define LCD_CURSOROFF 0x00                       
#define LCD_BLINKON 0x01                         // B   blink on
#define LCD_BLINKOFF 0x00                        
                                                 
// flags for display/cursor shift                // 0x10
#define LCD_DISPLAYMOVE 0x08                     // S/C Display Shift
#define LCD_CURSORMOVE 0x00                      // S/C Cursor Shift
#define LCD_MOVERIGHT 0x04                       // R/L Right Shift
#define LCD_MOVELEFT 0x00                        // R/L Left Shift
                                                 
// flags for function set                        // 0x20
#define LCD_8BITMODE 0x10                        // DL 8D must be set according chapter 10
#define LCD_4BITMODE 0x00                        // DL 4D (only in chapter 11. in chapter 10 not allowed)
#define LCD_2LINE 0x08                           // N  2R
#define LCD_1LINE 0x00                           // N  1R
#define LCD_5x10DOTS 0x04                        // F  5x10
#define LCD_5x8DOTS 0x00                         // F  5x7

// flags for backlight control                   // MISSING should be brought to I2C and SPI only
#define LCD_BACKLIGHT 0x08                       
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit 

// Error Codes
#define LCD_ERR_ADDR _BV(2)
#define LCD_ERR_CHIP _BV(3)


class LiquidCrystal_dummy : public Print {
  public:
    LiquidCrystal_dummy(uint8_t lcd_cols, uint8_t lcd_rows);         // constructor
    uint8_t begin();                             // my definition of how an object should be started
    uint8_t begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS );
    uint8_t init();                              // LCD API: Initializes the display - alias for begin()
    void clear();                                // LCD API: Clear the display and place cursor at 0,0 
    void home();                                 // LCD API: Home the cursor to 0,0 and leave displayed characters 
    void noDisplay();                            // Turn the display off (quickly)
    void display();                              // Turn the display on (quickly)
    void noBlink();                              // Turn off the blinking underline cursor
    void blink();                                // Turn oo the blinking underline cursor
    void noCursor();                             // Turn the block cursor off
    void cursor();                               // Turn the block cursor on
    void scrollDisplayLeft();                    // scroll the display without changing the RAM
    void scrollDisplayRight();                   // scroll the display without changing the RAM
    void printLeft();                            // MISSING tbc
    void printRight();                           // MISSING tbc
    void leftToRight();                          // This is for text that flows Left to Right
    void rightToLeft();                          // This is for text that flows Right to Left
    void shiftIncrement();                       // MISSING tbc
    void shiftDecrement();                       // MISSING tbc
    //virtual void noBacklight();                // implemented in hardware classes. delete 2021-06
    //virtual void backlight();                  // implemented in hardware classes. delete 2021-06
    void autoscroll();                           // This will 'right justify' text from the cursor
    void noAutoscroll();                         // This will 'left justify' text from the cursor
    void createChar(const uint8_t, const uint8_t[]);                       // Allows us to fill the first 8 CGRAM locations with custom characters
    void createChar_P(const uint8_t location, const uint8_t *charmap);     // the implementation for custom characters in PROGMEM      
    void setCursor(uint8_t, uint8_t);            // LCD API: with deviation! 
    void command(uint8_t);                       // LCD API: Send a command to the display, for commands not supported by the library
    virtual size_t write(uint8_t);               // the write method needed for the print class (parent)
    size_t writeOld(uint8_t);                    // legacy write of special characters >=0xC0
    virtual bool isConnected();                  // checks, if device is responding
    void createUml();                            // creates 3 German Umlauts using Special Characters 5, 6, and 7

    // compatibility API function aliases
    void blink_on();						                 // LCD API: alias for blink()
    void blink_off();       					           // LCD API: alias for noBlink()
    void cursor_on();      	 					           // LCD API: alias for cursor()
    void cursor_off();      					           // LCD API: alias for noCursor()
    //void setBacklight(uint8_t new_val);		     // LCD API (optional): alias for backlight() and noBacklight() - implemented in hardware classes
    void load_custom_character(uint8_t char_num, uint8_t *rows);	   // alias for createChar()
    void printstr(const char[]);                 // LCD API: Print a string without delay

    // Unsupported API functions (not implemented in this library)
    void setContrast(uint8_t val);               // LCD API (optional)
    uint8_t keypad();                            // LCD API (extend)
    void setDelay(int, int);                     // LCD API mandatory - but not implemented in this library
    void on();                                   // LCD API (optional)
    void off();                                  // LCD API (optional)
    uint8_t status();                            // LCD API (optional): MISSING tbd: could be implemented as alias of isConnected
    uint8_t init_bargraph(uint8_t graphtype);    // LCD API (Web4Robot)
    void draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);  // LCD API (Web4Robot)
    void draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end);    // LCD API (Web4Robot)

  protected:
    virtual void hwInit();                       // init hardware level
    virtual void send(uint8_t, uint8_t);         // virtual to ensure that local method will be used if available.
    virtual void write4bits(uint8_t);            // is in some classes override (but not all)
    virtual void expanderWrite(uint8_t);         // virtual to ensure that local method will be used if available. MISSING: should be brought to I2C and SPI class
    void pulseEnable(uint8_t);                   // MISSING: should be brought to I2C and SPI class
    uint8_t _displayfunction;                    // MISSING: tbc only used for classes with expander?
    uint8_t _displaycontrol;
    uint8_t _displaymode;        
    const uint8_t _numlines;                     // MISSING: tbc difference to _cols
    const uint8_t _cols;                         // columns of the display
    const uint8_t _rows;                         // how many rows has the display
    uint8_t _backlightval;                       // MISSING: stores if backlight is on or off, only needed for expander devices
    uint32_t special = 0;                        // noiasca: added to store special character
    uint8_t currentRow = 255;                    // noiasca: keep track of the actual row, needed for 4004 
};

#endif
