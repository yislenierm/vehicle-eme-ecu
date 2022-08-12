/*
  This is for displays with native Wire (I2C) support - e.g. Sureeno or Grove
  LCD driver AIP31068L
  RGB dirver PCA9633
  Native I2C Interface
  8bit mode
  
  Hardware
  - Sureeno with RGB Chip at 0x60           Available here: https://s.click.aliexpress.com/e/_dXgx0kh
  - Grove (Seeed) with RGB Chip at 0x62     Available here: https://amzn.to/352Kblx
  
  This classes are NOT for LED I2C backbacks
  
  open topics
  - rework .send method (split in send and write8bit)
  
  by noiasca
  
  2020-10-23 rework of backlight() / noBacklight(), rgbSET with autoincrement
  2020-10-20 setRGB overload for one variable HEX combined color code
  2020-09-05 initial version
*/

#pragma once
#include <Arduino.h>
#include <NoiascaLiquidCrystal.h>
#include <NoiascaHW/lcd_i2c.h>   
//#include <Wire.h>                    // could be done in lcd_i2c.h (but don't like it there neither)

#if defined(ARDUINO) && ARDUINO < 100
#warning "Your Arduino IDE might be outdated and this library might not work correctly. Consider to update your Arduino IDE to 1.8.10 or newer"
#endif

//#define ENABLE_ANALSIS               // enable internal I2C analysis  MISSING: to be deleted

// RGB IC PCA9633                      
constexpr uint8_t RGB_ADDR = 0x60;     // default value for the RGB chip
// datahseet table 7
constexpr uint8_t REG_MODE1 = 0x00;    // MODE1
constexpr uint8_t REG_MODE2 = 0x01;    // MODE2
constexpr uint8_t REG_BLUE =  0x02;    // pwm0
constexpr uint8_t REG_GREEN = 0x03;    // pwm1
constexpr uint8_t REG_RED =   0x04;    // pwm2
//                      0x06           // GRPPWM
//                      0x07           // GRPFREQ
constexpr uint8_t REG_OUTPUT = 0x08;   // LED driver output state, LEDOUT

// native 8bit Wire interface
class LiquidCrystal_Wire_base : public LiquidCrystal_I2C_base {
  public: 
#ifdef ENABLE_ANALSIS
    uint32_t err[6];                 // error counter
#endif 

    LiquidCrystal_Wire_base(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_I2C_base(lcd_Addr, lcd_cols, lcd_rows)
      {}

    uint8_t begin() { 
      return begin(_cols, _rows);
    }
    
    uint8_t begin(uint8_t cols, uint8_t lines, uint8_t dotsize = LCD_5x8DOTS) {     // compatibility to other LCD libraries: begin() without parameters
      uint8_t result = 0;
#ifdef DEBUG
      // Imho it's bad practise to call a hidden "begin" of other libraries. 
      // But this is just in case if the user has activated debug, 
      // so I consider this begin as ok
      // at least it makes my regression testing easier.
      Serial.begin(115200); 
      DEBUG_PRINTLN(F("Wire begin"));  
#endif
#if defined(__AVR__)
      if (TWCR == 0) {
        Wire.begin();                                          // only call when not started before
      }
#endif
    
      hwInit();        // low level hardware related initialisation, i.e. the ports or an expander

      if (isConnected())
      {
        (void)cols;                                            // avoid warning
        (void)lines;
        (void)dotsize;
        /*
        _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;       // noiasca - was in init_priv()
    
        if (lines > 1) {
          _displayfunction |= LCD_2LINE;
        }
        
        // for some 1 line displays you can select a 10 pixel high font
        if ((dotsize != 0) && (lines == 1)) {
          _displayfunction |= LCD_5x10DOTS;
        }
        */
        // Datasheet Page:14 chapter 10. Initialization Sequence
        // wait for more than 30ms after VDD rises to 4.5
        // Arduino can turn on way befer 4.5V so we'll wait longer (50 upwards)
        delay(500);
            
        // not in the AIP31068L datasheet, but let's do the three tries from the HD44810
        
        command(0x20 | 0x10 | 0x08 | 0x04);  // function set
        delayMicroseconds(wait);  
    
        // second try
        command(0x20 | 0x10 | 0x08 | 0x04);  // function set
        delayMicroseconds(wait);       
    
        // third go!
        command(0x20 | 0x10 | 0x08 | 0x04);  // function set
        delayMicroseconds(wait);      
    
        // use the full "8bit" so no typicall "4bit" change
        
        // function set
        // set # lines, font size, etc.
        //command(LCD_FUNCTIONSET | LCD_CURSORSHIFT | LCD_2LINE);
        command(0x20 | 0x10 | 0x08 | 0x04);
        delayMicroseconds(wait);
    
        // display ON/OFF control
        // turn the display on with no cursor or blinking default
        //command(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
        command(0x08 | 0x04);
        delayMicroseconds(wait);
    
        // display clear
        //clear();
        command(0x01);
        delayMicroseconds(waitlong);
    
        // entry mode set
        // Initialize to default text direction (for roman languages)
        //command(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
        command(0x04 | 0x02);
        delayMicroseconds(wait);  // not in datasheet
      }
      else
      {
        result = LCD_ERR_ADDR;
      }
      return result;
    }
            
  protected:
    // MISSING: this is a massive shortcut (and dirty) should be a write8bit
    void send(uint8_t value, uint8_t mode) override {
      Wire.beginTransmission(_Addr);
      if (mode == Rs) 
         Wire.write(LCD_SETCGRAMADDR);           // 0x40 ... characters
      else 
         Wire.write(0);                          // 0x80  ... LCD_SETDDRAMADDR wir setzen aber 0!
      Wire.write(value);
#ifdef ENABLE_ANALSIS
      byte result = Wire.endTransmission();      // transmit
      if (result < 6) err[result]++;             // fill error counter
#else
      Wire.endTransmission();
#endif
    }  
  
  private:
    const uint8_t wait = 43 + 7;                 // many are 39us, the slowest is 43us, 7us is just to get a nice number - why? because we can.
    const uint16_t waitlong = 1530 + 70;         // 1530 for slow commands
};

/*
    Wire/I2c Display with RGB Backlight PCA9633
    Sureeno or Grove 
*/
// native 8bit Wire interface
class LiquidCrystal_Wire_RGB : public LiquidCrystal_Wire_base {
  protected:
    const uint8_t rgbAddr;                                 // hardwired on Sureeno display
    byte blRed = 127, blGreen = 127, blBlue = 127;         // backlight default colors (medium grey/white)
    // _backlightval from base class was reused for backlight brightness   
    using CallBack = uint8_t (*)(uint32_t &special, uint8_t &value);
    CallBack funcPtr;  
  
    public:
    // defaulted rgbAddr, defaulted callback function pointer
    LiquidCrystal_Wire_RGB(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_Wire_base(lcd_Addr, lcd_cols, lcd_rows),
      rgbAddr(RGB_ADDR),               // default value from define
      funcPtr(convert)                 // function pointer to default converter
      {
        _backlightval = 255;
      }
      
    // defaulted rgbAddr but dedicated function pointer
    LiquidCrystal_Wire_RGB(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, CallBack funcPtr) : 
      LiquidCrystal_Wire_base(lcd_Addr, lcd_cols, lcd_rows),
      rgbAddr(RGB_ADDR),               // default value from define
      funcPtr(funcPtr)                 // function pointer to individual converter
      {
        _backlightval = 255;
      }
    
    // dedicated rgbAddr but defaulted callback function pointer
    LiquidCrystal_Wire_RGB(uint8_t lcd_Addr, uint8_t rgbAddr, uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_Wire_base(lcd_Addr, lcd_cols, lcd_rows),
      rgbAddr(rgbAddr),
      funcPtr(convert)                 // function pointer to default converter
      {
        _backlightval = 255;
      }
      
    // dedicated rgbAddr and dedicated function pointer
    LiquidCrystal_Wire_RGB(uint8_t lcd_Addr, uint8_t rgbAddr, uint8_t lcd_cols, uint8_t lcd_rows, CallBack funcPtr) : 
      LiquidCrystal_Wire_base(lcd_Addr, lcd_cols, lcd_rows),
      rgbAddr(rgbAddr),
      funcPtr(funcPtr)                 // function pointer to individual converter
      {
        _backlightval = 255;
      }

    inline size_t write(uint8_t value) {
      DEBUG_PRINTLN(F("Wire_RGB write"));
      switch(funcPtr (special, value))
      {
        case NOPRINT :                 // don't print
          break;                       
        case ADDE :                    // print an additional e after character
          send(value, Rs);             
          send('e', Rs);               // add a small e after the printed character
          break;                       
        default :                      // includes PRINT: just print
          send(value, Rs);
      }
      return 1; // allways assume success
    }        
      
    /*    
       Turn the (optional) backlight on
       for these displays it's done by hardware with the RGB chip
    */               
    void backlight(void) {
      //_backlightval = LCD_BACKLIGHT;
      setRegRGB(REG_OUTPUT, 0xFF);     // table 13: LED driver x individual brightness and group dimming/blinking can be controlled through its PWMx register and the GRPPWM registers.
    }
    
    /*    
       switch on the backlight
       for these displays it's done by hardware with the RGB chip
    */
    void noBacklight(void) {
      //_backlightval = LCD_NOBACKLIGHT;
      setRegRGB(REG_OUTPUT, 0x00);     // table 13: LED driver x is off
    }

    /*    
       set brightness of LED backlight
    */    
    void setBacklight(uint8_t new_val) override
    {
      _backlightval = new_val;         // MISSING: to be done: don't missuse _backlightval - instead use new variable
      setRGB(blRed, blGreen, blBlue); 
    }

    /*    
       switch on the backlight LED blinking
    */
    void blinkBacklight(void)
    { 
      // blinking period is controlled through 256 linear steps from 00h (41 ms, frequency 24 Hz) to FFh (10.73 s).
      // blink period in seconds = (<reg 7> + 1) / 24
      // on/off ratio = <reg 6> / 256
      setRegRGB(0x07, 0x17);           // blink every second
      setRegRGB(0x06, 0x7f);           // half on, half off     GRPPWM
    }
    
    /*    
       switch off the backlight LED blinking
    */    
    void noBlinkBacklight(void) 
    {
      setRegRGB(0x07, 0x00);           // GRPFREQ
      setRegRGB(0x06, 0xff);           // GRPPWM
    }
    
    /*
       initiliazes the general hardware
    */
    void hwInit(void) override{        // low level hardware related initialisation, i.e. the ports or an expander
      DEBUG_PRINTLN(F("Wire hwInit"));
      initRGB();
      //MISSING: delay for display? - tbc
    }
    
    /*
       initiliazes the RGB driver chip
       MISSING: make it private
    */
    void initRGB()
    {
      DEBUG_PRINTLN(F("Wire initRGB"));
      // reset chips on bus            // datasheet chapter 7.6 Software Reset
      Wire.beginTransmission(0x03);    // SWRST I2C-bus address ‘0000 011’ 
      Wire.write(0xA5);                // Byte 1 = A5h: the PCA9633 acknowledges this value only.
      Wire.write(0x5A);                // Byte 2 = 5Ah: the PCA9633 acknowledges this value only.
      Wire.endTransmission();          // the PCA9633 then resets to the default value (power-up value)        
      // backlight init
      setRegRGB(REG_MODE1, 0);         // table 8: Normal mode, does not respond to I2C-bus subaddress, does not respond to LED All Call I2C-bus address
      // set LEDs controllable by both PWM and GRPPWM registers
      setRegRGB(REG_OUTPUT, 0xFF);     // table 13: LED driver x individual brightness and group dimming/blinking can be controlled through its PWMx register and the GRPPWM registers.
      // set MODE2 values
      // 0010 0000 -> 0x20  (DMBLNK to 1, ie blinky mode)
      setRegRGB(REG_MODE2, 0x20);      // table 9: Bit 5 Group control = blinking
    }
    
    /* 
        sets a RGB Chip register to a value (i.e. one specific color register)
        Low Level Function to I2C Registers
        MISSING: tbd: make it protected
    */
    void setRegRGB(unsigned char reg, unsigned char value) {
      Wire.beginTransmission(rgbAddr);
      Wire.write(reg);
      Wire.write(value);
      Wire.endTransmission();
    }
    
    /* 
        sets all three backlight colors
        Sends data with autoincrement, which should be faster but needs 32 bytes more than the former version 
    */
    void setRGB(unsigned char r, unsigned char g, unsigned char b) {   
      // 
      blRed = r;
      blGreen = g;
      blBlue = b;
      const byte autoincrement = 0x80;  // datasheet table 6, Auto-Increment for all registers. D3, D2, D1, D0 roll over to ‘0000’ after the last register (1100) is accessed.
      Wire.beginTransmission(rgbAddr);
      Wire.write((REG_BLUE | autoincrement));
      Wire.write(b * _backlightval / 255U);
      Wire.write(g * _backlightval / 255U);
      Wire.write(r * _backlightval / 255U);
      Wire.endTransmission();     
    }
    /*
    // to be finally deleted in 2021
    void setRGB_OLD(unsigned char r, unsigned char g, unsigned char b) {
      blRed = r;
      blGreen = g;
      blBlue = b;
      setRegRGB(REG_RED, r * _backlightval / 255U);
      setRegRGB(REG_GREEN, g * _backlightval / 255U);
      setRegRGB(REG_BLUE, b * _backlightval / 255U);      
    }
    */
   
    /*
      sets the three backlight colors 
      (parameter overload)
    */
    void setRGB(uint32_t newColor) {
      uint8_t r = newColor >> 16;
      uint8_t g = (newColor & 0xFF00) >> 8;
      uint8_t b = newColor & 0xFF;
      setRGB(r, g, b);  
    }
};