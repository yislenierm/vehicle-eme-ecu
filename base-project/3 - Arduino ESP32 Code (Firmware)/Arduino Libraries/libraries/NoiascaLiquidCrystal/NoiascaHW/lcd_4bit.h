/*
   Parallel 4bit variant - 440 - 4004
   
   Open topics
   - Support RW pin
   - bring digitalWriteFast into class
   
   by noiasca
   2021-04-04 extended for 4004
   2021-01-08 changed access specifier
   2021-01-04 minor optimizations (const dataPin, scope of digitalWriteFast)
   2020-10-09 digitalWriteFast
   2020-09-05
*/
#pragma once
#include <NoiascaLiquidCrystal.h>
#include <Arduino.h>

#if defined(ARDUINO) && ARDUINO < 100
#warning "Your Arduino IDE might be outdated and this library might not work correctly. Consider to update your Arduino IDE to 1.8.10 or newer"
#endif

#define FAST                           // activates faster routines for digitalWrite - deactivate if you don't want to use
#if defined(FAST) && !defined(ARDUINO_ARCH_ESP8266) && !defined(ARDUINO_ARCH_ESP32)
#define DIGITALWRITE digitalWriteFast
#else
#define DIGITALWRITE digitalWrite      // use the standard function from the core
#if defined(FAST)
#undef FAST
#endif
#endif

//tbd
typedef enum { POSITIVE, NEGATIVE, POSITIVE_FAULTY, NONE=255} t_backlightPol;

/*
   4bit base class
*/
class LiquidCrystal_4bit_base : public LiquidCrystal_dummy {
  public:
    // 12 Parameters (full)
    LiquidCrystal_4bit_base(uint8_t rsPin, uint8_t rwPin, uint8_t enPin, uint8_t en2Pin, 
                            uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, 
                            uint8_t blPin, t_backlightPol blType, 
                            uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_dummy(lcd_cols, lcd_rows),
      rsPin(rsPin), enPin(enPin), en2Pin(en2Pin),
      blPin(blPin), blType(blType),
      dataPin{d4Pin, d5Pin, d6Pin, d7Pin}
      {(void)rwPin;}                   // not used in current version
      
    // 9 Parameters
    LiquidCrystal_4bit_base(uint8_t rsPin, uint8_t enPin,  
                            uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, 
                            uint8_t blPin,
                            uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_dummy(lcd_cols, lcd_rows),
      rsPin(rsPin), enPin(enPin), en2Pin(255), 
      blPin(blPin), blType(POSITIVE_FAULTY),
      dataPin{d4Pin, d5Pin, d6Pin, d7Pin}
      {}      
      
    bool isConnected() override {
      return true;                     // dummy, assume success
    }

    uint8_t begin() {                  // backward compatibility
      return begin(_cols, _rows);
    }
    
    uint8_t begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS) 
    // uint8_t begin(uint8_t cols, uint8_t lines, uint8_t dotsize = LCD_5x8DOTS) // old signature till 1.2.3
    {     // compatibility to other LCD libraries: begin() without parameters
      uint8_t result = 0;
#ifdef DEBUG
      // IMHO it is bad practise to call a hidden "begin" of other libraries. 
      // But this is just in case if the user has activated DEBUG 
      // so I consider this begin as ok
      // and it makes my regression testing easier.
      Serial.begin(115200); 
      DEBUG_PRINTLN(F("4bit_base begin"));  
#endif      
          
      if (rows > 1) {
        _displayfunction |= LCD_2LINE;
      }
    
      // for some 1 line displays you can select a 10 pixel high font
      if ((charsize != LCD_5x8DOTS) && (rows == 1)) {
        _displayfunction |= LCD_5x10DOTS;
      }
    
      hwInit();
      (void)cols;   
      
//    if (! (_displayfunction & LCD_8BITMODE)) {   // 8 bit mode not supported - therefore if commented out
        // this is according to the hitachi HD44780 datasheet
        // figure 24, pg 46
        // 4 bit mode 
    
        // we start in 8bit mode, try to set 4 bit mode
        write4bits(0x03);
        delay(5); // datasheet min 4.1ms - delay enables some internal hardware specific processing
    
        // second try
        write4bits(0x03);
        delay(1); // datasheet min 100us
        
        // third go!
        write4bits(0x03); 
        delay(1); // because everyone waits 100us - 150us
    
    // finally, set to 4-bit interface
        write4bits(0x02); 
//     }  // 8 bit mode not supported - therefore bracket commented out
/*      
      else {
        // this is according to the hitachi HD44780 datasheet
        // page 45 figure 23
        // 8 bit mode not supported
    
        // Send function set command sequence
        command(LCD_FUNCTIONSET | _displayfunction);
        delay(5); // datasheet min 4.1ms
    
        // second try
        command(LCD_FUNCTIONSET | _displayfunction);
        delay(1); // datasheet min 100us
    
        // third go
        command(LCD_FUNCTIONSET | _displayfunction);
      }
*/    
      // finally, set # lines, font size, etc.
      command(LCD_FUNCTIONSET | _displayfunction);  
    
      // turn the display on with no cursor or blinking default
      _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;  
      display();
    
      // clear it off
      clear();
    
      // Initialize to default text direction (for romance languages)
      _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
      // set the entry mode
      command(LCD_ENTRYMODESET | _displaymode);
    
      return result;
    }    
    
    // Turn the (optional) backlight off/on
    void noBacklight(void) {
      //_backlightval = LCD_NOBACKLIGHT;
      if (blPin < 255)
        pinMode(blPin, OUTPUT);        // turn off backlight SAFE
    }
    
    void backlight(void) {
      //_backlightval = LCD_BACKLIGHT;
      if (blPin < 255)
        pinMode(blPin, INPUT);         // turn on backlight SAFE
    }
    
    // alias for LCD API
    void setBacklight(uint8_t new_val) {
      if (new_val) {
        backlight();		               // turn backlight on
      } else {
        noBacklight();		             // turn backlight off
      }
    }
    
  protected:
    const uint8_t rsPin, enPin, en2Pin, blPin;     // GPIOs where LCD is connected to
    const t_backlightPol blType;       // polarity and type of backlight control
    const uint8_t dataPin[4];          // GPIOs for data pins of LCD - only for 4 bit

#if defined(FAST)
    // I expect that people know what they do with their ports, 
    // therefore I use a slimmer (and faster) version of digitalWrite
    // if you encounter any problems with newer boards - deactivate FAST in the settings.
    void digitalWriteFast(uint8_t pin, uint8_t val) 
      {
      	uint8_t bit = digitalPinToBitMask(pin);
      	uint8_t port = digitalPinToPort(pin);
      	volatile uint8_t *out = portOutputRegister(port);
      	if (val == LOW) {
      		*out &= ~bit;
      	} else {
      		*out |= bit;
      	}
      }
#endif
  
    void write4bits(uint8_t value) override {
      DEBUG_PRINTLN(F("4bit_base write4bits()"));
      for (uint8_t i = 0; i < 4; i++) {
        DIGITALWRITE(dataPin[i], (value >> i) & 0x01);
      }
      pulseEnable();
    }
    
    void hwInit() override {
      DEBUG_PRINTLN(F("4bit_base hwInit()"));
      pinMode(rsPin, OUTPUT);
      DIGITALWRITE(rsPin, LOW);
      //if (rwPin != 255) { 
      //  pinMode(rwPin, OUTPUT);
      //  DIGITALWRITE(rwPin, LOW); 
      //}
      pinMode(enPin, OUTPUT);
      if (en2Pin < 255) pinMode(en2Pin, OUTPUT);
      DIGITALWRITE(enPin, LOW);
      if (blPin < 255)
      {
        DIGITALWRITE(blPin, LOW);
        pinMode(blPin, OUTPUT);    
      }
      for (uint8_t i = 0; i < 4; i++)
        pinMode(dataPin[i], OUTPUT);
    }   
    
    // write either command or data, with automatic 4/8-bit selection
    void send(uint8_t value, uint8_t mode) override {
      DEBUG_PRINTLN(F("4bit_base send()"));
      DIGITALWRITE(rsPin, mode);
      /*
      // if there is a RW pin indicated, set it low to Write
      if (_rw_pin != 255) { 
        DIGITALWRITE(_rw_pin, LOW);
      }
      if (_displayfunction & LCD_8BITMODE) {
        write8bits(value); 
      } else {
        write4bits(value >> 4);
        write4bits(value);
      }
      */
      write4bits(value >> 4);
      write4bits(value);
    }

  protected:
   void pulseEnable(void)                        // till 1.2.3
   // void pulseEnable(uint8_t _data = 0)        // MISSING tbd 
   {
      DEBUG_PRINTLN(F("4bit_base pulseEnable()"));
      // (void)_data;                  // not used in 4bit
      //DIGITALWRITE(enPin, LOW);      // should be LOW anyway
      //delayMicroseconds(1);  
      
      if (_cols == 40 && _rows == 4 && currentRow == 255)
      {     
        DIGITALWRITE(enPin, HIGH);
        DIGITALWRITE(en2Pin, HIGH);
        delayMicroseconds(1);          // enable pulse must be >450ns
        DIGITALWRITE(enPin, LOW);
        DIGITALWRITE(en2Pin, LOW);
        delayMicroseconds(50);         // commands need > 37us to settle
      }
      else if (_cols == 40 && _rows == 4 && currentRow >= 2 )  // the compiler can & will optimzize this
      {
        DIGITALWRITE(en2Pin, HIGH);
        delayMicroseconds(1);          // enable pulse must be >450ns
        DIGITALWRITE(en2Pin, LOW);
        delayMicroseconds(50);         // commands need > 37us to settle  
      }
      else
      {
        DIGITALWRITE(enPin, HIGH);
        delayMicroseconds(1);          // enable pulse must be >450ns
        DIGITALWRITE(enPin, LOW);
        delayMicroseconds(50);         // commands need > 37us to settle
      }
    }
};


/*
   4bit class with special character support
*/
class LiquidCrystal_4bit : public LiquidCrystal_4bit_base {
  protected:
    using CallBack = uint8_t (*)(uint32_t &special, uint8_t &value);
    CallBack funcPtr;        // callback function to the converter which should be used in .write()
    
  public:
    // 12 pin parameter
    LiquidCrystal_4bit(uint8_t rsPin, uint8_t rwPin, uint8_t enPin, uint8_t en2Pin,
                       uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, 
                       uint8_t blPin, t_backlightPol blType,
                       uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_4bit_base(rsPin, rwPin, enPin, en2Pin, d4Pin, d5Pin, d6Pin, d7Pin, blPin, blType, lcd_cols, lcd_rows),
      funcPtr(convert)       // function pointer to default converter      
      {}
    
    // 12 pin parameter + function Pointer
    LiquidCrystal_4bit(uint8_t rsPin, uint8_t rwPin, uint8_t enPin, uint8_t en2Pin, 
                       uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, 
                       uint8_t blPin, t_backlightPol blType,
                       uint8_t lcd_cols, uint8_t lcd_rows,
                       CallBack funcPtr) : 
      LiquidCrystal_4bit_base(rsPin, rwPin, enPin, en2Pin, d4Pin, d5Pin, d6Pin, d7Pin, blPin, blType, lcd_cols, lcd_rows),
      funcPtr(funcPtr)   
      {}

    // 9 pin parameter (backward compatibility to 1.2.3)
    LiquidCrystal_4bit(uint8_t rsPin, uint8_t enPin,
                       uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, 
                       uint8_t blPin, 
                       uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_4bit_base(rsPin, 255, enPin, 255, d4Pin, d5Pin, d6Pin, d7Pin, blPin, POSITIVE_FAULTY, lcd_cols, lcd_rows),
      funcPtr(convert)       // function pointer to default converter      
      {}          
      
    // 9 pin parameter + function Pointer (backward compatibility to 1.2.3)
    LiquidCrystal_4bit(uint8_t rsPin, uint8_t enPin, 
                       uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin, 
                       uint8_t blPin, 
                       uint8_t lcd_cols, uint8_t lcd_rows,
                       CallBack funcPtr) : 
      LiquidCrystal_4bit_base(rsPin, 255, enPin, 255, d4Pin, d5Pin, d6Pin, d7Pin, blPin, POSITIVE_FAULTY, lcd_cols, lcd_rows),
      funcPtr(funcPtr)   
      {}      

    inline size_t write(uint8_t value) {
      DEBUG_PRINTLN(F("4bit write()"));
      switch(funcPtr (special, value))
      {
        case NOPRINT :       // don't print
          break;
        case ADDE :          // print an additional e after character
          send(value, Rs);
          send('e', Rs);     // add a small e after the printed character
          break;
        default :            // includes 1: just print
          send(value, Rs);
      }
      return 1;
    }
};

