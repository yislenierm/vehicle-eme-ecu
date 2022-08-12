/*
   Noiasca Liquid Crystal
   
   Based on the work of DFRobot
   
   by noiasca
   2021-04-04 extended for 4004
   2021-02-15 reorganised converter files (deleted converters from this file)
   2021-02-14 replaced ANSI by ASCII (kept ANSI as alias)
   2021-02-12 Cyrillic converter, SPLC780D1_002A Cyrillic
   2020-09-20 SPLC780D1_003A European
*/

#include <NoiascaLiquidCrystal.h>
//#include <inttypes.h>
//#include "Arduino.h"

#if defined(ARDUINO) && ARDUINO < 100
#warning "Your Arduino IDE might be outdated and this library might not work correctly. Consider to update your Arduino IDE to 1.8.10 or newer"
#endif

LiquidCrystal_dummy::LiquidCrystal_dummy(uint8_t lcd_cols, uint8_t lcd_rows) :
  _numlines{lcd_rows},
  _cols{lcd_cols},
  _rows{lcd_rows}
{
  _backlightval = LCD_NOBACKLIGHT;
}

// legacy write of special characters >= 0xC0
// it is more or less an original write method from Adafruit Version 1.1.2

size_t LiquidCrystal_dummy::writeOld(uint8_t value) {
  send(value, Rs);
  return 1;
}

inline size_t LiquidCrystal_dummy::write(uint8_t value) {
  DEBUG_PRINTLN(F("dummy write"));
  send(value, Rs);
  return 1;
}

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

uint8_t LiquidCrystal_dummy::init() {                                  // alias method, backward compatibility to Adafruit LiquidCrystal I2C
  return begin(_cols, _rows);
}

uint8_t LiquidCrystal_dummy::begin() {                                 // compatibility to other LCD libraries: begin() without parameters
  return begin(_cols, _rows);
}

uint8_t LiquidCrystal_dummy::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {     // dotsize defaulted in .h
  uint8_t result = 0;
#ifdef DEBUG
      // Imho it's bad practise to call a hidden "begin" of other libraries. 
      // But this is just in case if the user has activated debug, 
      // so I consider this begin as ok
      // at least it makes my regression testing easier.
      Serial.begin(115200); 
      DEBUG_PRINTLN(F("dummy begin"));  
#endif
  hwInit();        // low level hardware related initialisation, i.e. the ports or an expander

  if (isConnected())
  {
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;       // noiasca - was in init_priv()

    (void)cols;                                                      // noiasca: avoid warning
    if (lines > 1) {
      _displayfunction |= LCD_2LINE;
    }

    // for some 1 line displays you can select a 10 pixel high font
    if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
      _displayfunction |= LCD_5x10DOTS;
    }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
    delay(50);

    // Now we pull both RS and R/W low to begin commands
    expanderWrite(_backlightval);	// reset expander and turn backlight off (Bit 8 =1)  // MISSING: checken, was tun bei Klassen ohne expander
    delay(100);

    // put the LCD into 4 bit mode
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    write4bits(0x03 << 4);
    delay(5); // datasheet min 4.1ms

    // second try
    write4bits(0x03 << 4);
    delay(1); // datasheet min 100us

    // third go!
    write4bits(0x03 << 4);
    delay(1); // because everyone waits 100us

    // now we are in 8bit mode
    // finally, set to 4-bit interface
    write4bits(0x02 << 4); 

    // set # lines, font size, etc.
    command(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();

    // clear it off
    clear();

    // Initialize to default text direction (for roman languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

    // set the entry mode
    command(LCD_ENTRYMODESET | _displaymode);

    home();
  }
  else
  {
    result = LCD_ERR_ADDR;
  }

  return result;
}

/********** high level commands, for the user! */
void LiquidCrystal_dummy::clear() {
  // 4004 activate both displays
  if  (_cols == 40 && _rows == 4) currentRow = 255;
  command(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
  currentRow = 0;
  delayMicroseconds(2000);   // this command takes a long time!
}

void LiquidCrystal_dummy::home() {
  currentRow = 0;
  command(LCD_RETURNHOME);   // set cursor position to zero
  delayMicroseconds(2000);   // this command takes a long time!
}

void LiquidCrystal_dummy::setCursor(uint8_t col, uint8_t row) {
  if ( row > _numlines ) {
    row = _numlines - 1;     // we count rows starting w/0
  }
  currentRow = row;
  if  (_cols == 40 && _rows == 4)
  {
    const uint8_t row_offsets[] = { 0x00, 0x40, 0x00, 0x40 };  // for 4004
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
  }
  else
  {
    const uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };  // default for 2004
    command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
  }
}

// Turn the display on/off (quickly)
void LiquidCrystal_dummy::noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_dummy::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_dummy::noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_dummy::cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor (block)
void LiquidCrystal_dummy::noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

void LiquidCrystal_dummy::blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_dummy::scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_dummy::scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_dummy::leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_dummy::rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_dummy::autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_dummy::noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_dummy::createChar(uint8_t location, const uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (uint8_t i = 0; i < 8; i++) {
    writeOld(charmap[i]); // reworked to writeOld
  }
}

// noiasca read custom character from  PROGMEM
void LiquidCrystal_dummy::createChar_P(uint8_t location, const uint8_t *charmap) {
	location &= 0x7; // we only have 8 locations 0-7
	command(LCD_SETCGRAMADDR | (location << 3));
	for(uint8_t i = 0; i < 8; i++)
	{
    writeOld(pgm_read_byte(charmap + i));
	}
}


/*
// Turn the (optional) backlight off/on
void LiquidCrystal_dummy::noBacklight(void) {
  _backlightval = LCD_NOBACKLIGHT;
  expanderWrite(0);
}

void LiquidCrystal_dummy::backlight(void) {
  _backlightval = LCD_BACKLIGHT;
  expanderWrite(0);
}
*/

/*********** mid level commands, for sending data/cmds */

inline void LiquidCrystal_dummy::command(uint8_t value) {
  send(value, 0);
}

/************ low level data pushing commands **********/

// write either command or data
void LiquidCrystal_dummy::send(uint8_t value, uint8_t mode) {
  DEBUG_PRINTLN(F("dummy send"));
  uint8_t highnib = value & 0xf0;
  uint8_t lownib = (value << 4) & 0xf0;
  write4bits((highnib) | mode);
  write4bits((lownib) | mode);
}

void LiquidCrystal_dummy::write4bits(uint8_t value) {
  DEBUG_PRINTLN(F("dummy write4bits"));
  expanderWrite(value);
  pulseEnable(value);
}

void LiquidCrystal_dummy::expanderWrite(uint8_t _data) {
  DEBUG_PRINTLN(F("dummy expanderWrite"));
  (void)_data; // avoid warning
  //Wire.beginTransmission(_Addr);
  //Wire.write((int)(_data) | _backlightval);
  //Wire.endTransmission();
}

void LiquidCrystal_dummy::pulseEnable(uint8_t _data) {
  expanderWrite(_data | En); // En high
  delayMicroseconds(1);		   // enable pulse must be >450ns

  expanderWrite(_data & ~En);// En low
  delayMicroseconds(50);		 // commands need > 37us to settle
}


bool LiquidCrystal_dummy::isConnected()          // dummy only
{
  return true;     // assume success
}

void LiquidCrystal_dummy::hwInit()               // dummy only
{}

// Alias functions

void LiquidCrystal_dummy::cursor_on() {
  cursor();
}

void LiquidCrystal_dummy::cursor_off() {
  noCursor();
}

void LiquidCrystal_dummy::blink_on() {
  blink();
}

void LiquidCrystal_dummy::blink_off() {
  noBlink();
}

void LiquidCrystal_dummy::load_custom_character(uint8_t char_num, uint8_t *rows) {
  createChar(char_num, rows);
}

/*
// will be implented in the hw classes
void LiquidCrystal_dummy::setBacklight(uint8_t new_val) {
  if (new_val) {
    backlight();		  // turn backlight on
  } else {
    noBacklight();		// turn backlight off
  }
}
*/

void LiquidCrystal_dummy::printstr(const char c[]) {
  //This function is not identical to the function used for "real" I2C displays
  //it's here so the user sketch doesn't have to be changed
  print(c);
}

// unsupported API functions
void LiquidCrystal_dummy::off() {}
void LiquidCrystal_dummy::on() {}
void LiquidCrystal_dummy::setDelay (int cmdDelay, int charDelay) {
  (void)cmdDelay;  // avoid warning
  (void)charDelay;
}
uint8_t LiquidCrystal_dummy::status() {
  return 0;
}
uint8_t LiquidCrystal_dummy::keypad() {
  return 0;
}
uint8_t LiquidCrystal_dummy::init_bargraph(uint8_t graphtype) {
  (void)graphtype; // avoid warning
  return 0;
}
void LiquidCrystal_dummy::draw_horizontal_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_col_end) {
  (void)row;       // avoid warning
  (void)column;
  (void)len;
  (void)pixel_col_end;
}
void LiquidCrystal_dummy::draw_vertical_graph(uint8_t row, uint8_t column, uint8_t len,  uint8_t pixel_row_end) {
  (void)row;       // avoid warning
  (void)column;
  (void)len;
  (void)pixel_row_end;
}
void LiquidCrystal_dummy::setContrast(uint8_t new_val) {
  (void)new_val;   // avoid warning
}

/*
// create 3 German Umlauts using Special Characters 5, 6, and
// has to be called in the user sketch individually if needed
// even this variant looks more consistant, it will cost 32bytes more than the old one
void LiquidCrystal_dummy::createUml() { 
  DEBUG_PRINTLN(F("dummy createUml"));
  createChar_P(5, capital_a_diareses);    // Ä
  createChar_P(6, capital_o_diareses);    // Ö 
  createChar_P(7, capital_u_diareses);    // Ü 
}
*/

// create 3 German Umlauts using Special Characters 5, 6, and
// has to be called in the user sketch individually if needed
// even this variant looks redundandt, it will spare 32bytes flash than the new one

void LiquidCrystal_dummy::createUml() { 
  DEBUG_PRINTLN(F("dummy createUml"));
  for (uint8_t u = 0; u < 3; u++)
  {
    byte location = 5 + u;   // offset 5 for first special character
    command(LCD_SETCGRAMADDR | (location << 3));
    for (uint8_t i = 0; i < 8; i++) {
      writeOld(pgm_read_byte_near(&UML[u][i]));
    }
  }
}