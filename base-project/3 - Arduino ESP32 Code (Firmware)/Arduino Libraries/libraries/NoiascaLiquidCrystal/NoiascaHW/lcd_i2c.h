/*
   I2C PCF8574 4bit variants
   
   2021-02-28 minor cleanup & comments
   2020-09-05
*/
#pragma once
#include <Arduino.h>
#include <NoiascaLiquidCrystal.h>
#include <Wire.h>

#if defined(ARDUINO) && ARDUINO < 100
#warning "Your Arduino IDE might be outdated and this library might not work correctly. Consider to update your Arduino IDE to 1.8.10 or newer"
#endif

/*
   I2C base class
*/


class LiquidCrystal_I2C_base : public LiquidCrystal_dummy {
  public:
    LiquidCrystal_I2C_base(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) :
      LiquidCrystal_dummy(lcd_cols, lcd_rows),
      _Addr(lcd_Addr) 
    {}
    
    // MISSING: 2021-02-28 deleted virtual
    //                                           // LCD API (Optional Function): Set the backlight off/on, or set Backlight brightness (0-255)    
    void setBacklight(uint8_t new_val) {
      DEBUG_PRINTLN(F("I2C_Base setBackLight"));
      if (new_val) {
        backlight();		  // turn backlight on
      } else {
        noBacklight();		// turn backlight off
      }
    }
    
    // Turn the (optional) backlight off/on
    void noBacklight(void) {                     // Alias Function for compatibility to other Libraries
      _backlightval = LCD_NOBACKLIGHT;
      expanderWrite(0);
    }
    
    void backlight(void) {                       // Alias Function for compatibility to other Libraries
      _backlightval = LCD_BACKLIGHT;
      expanderWrite(0);
    }

    bool isConnected()
    {
      Wire.beginTransmission(_Addr);
      if (Wire.endTransmission() == 0)           // See if something ack's at this address
      {
        /*
          if (getID() == CHIP_ID_CONSTANT)       // Make sure ID is what we expect
          {
            return true;
          }
          return false;
        */
        return true;
      }
      return false;
    }

  protected:
    const uint8_t _Addr;                         // I2C address of expander
    
    /*
       Lowest level of hardware access 
    */
    void expanderWrite(uint8_t _data) override {
      DEBUG_PRINTLN(F("I2C_base expanderWrite"));
      Wire.beginTransmission(_Addr);
      Wire.write((int)(_data) | _backlightval);
      Wire.endTransmission();
    }

    void hwInit() override {
      DEBUG_PRINTLN(F("I2C_base hwInit"));
#if defined(__AVR__)
      if (TWCR == 0) {
        Wire.begin();                  // only call when not started before
      }
#endif
    }
};

/*
   I2C default class with special character support
*/
class LiquidCrystal_I2C : public LiquidCrystal_I2C_base {
  protected:
    using CallBack = uint8_t (*)(uint32_t &special, uint8_t &value);
    CallBack funcPtr;  
    
  public:
    LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) :
      LiquidCrystal_I2C_base(lcd_Addr, lcd_cols, lcd_rows),
      funcPtr(convert)       // function pointer to default converter
      {}
    
    // with function pointer to individual callback
    LiquidCrystal_I2C(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, CallBack funcPtr) :
      LiquidCrystal_I2C_base(lcd_Addr, lcd_cols, lcd_rows),
      funcPtr(funcPtr)       // function pointer to individual converter
      {}   
   
    inline size_t write(uint8_t value) {
      DEBUG_PRINTLN(F("I2C write"));
      switch(funcPtr (special, value))
      {
        case NOPRINT :       // don't print
          break;
        case PRINT2 :        // print from second pattern. MISSING: to be checked if separate variant for the ST7070 classes
          blink();
          send ( value, Rs);
          noBlink();
          break;
        case ADDE :          // print an additional e after character
          send(value, Rs);
          send('e', Rs);     // add a small e after the printed character
          break;
        default :            // includes PRINT: just print
          send(value, Rs);
      }
      return 1;              // allways assume success
    }  
};

/*
   I2C class replaces capital Ä with Ae
*/
class LiquidCrystal_I2C_Ae : public LiquidCrystal_I2C {
  public:
    LiquidCrystal_I2C_Ae(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows, convert_ae) {}
};

/*
   I2C small: adds 3 Variables for the replacement characters, defaults to the small character. Ä -> ä 
*/
class LiquidCrystal_I2C_Small : public LiquidCrystal_I2C {
  public:
    LiquidCrystal_I2C_Small(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows, convert_small) {}
};

/*
   I2C specials: uses 3 special characters for capital letters Ä Ö Ü 
*/
class LiquidCrystal_I2C_Special : public LiquidCrystal_I2C {
  public:
    LiquidCrystal_I2C_Special(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : 
      LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows, convert_special) 
      {}
    
  private:
    // here was the createUml - now public in dummy
};

/*
   I2C ST7070: uses the extended characters of the ST7070
*/
class LiquidCrystal_I2C_ST7070 : public LiquidCrystal_I2C {
  public:
    LiquidCrystal_I2C_ST7070(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) :
      LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows, convert_ST7070) {}
};

/*
   I2C ST7070_Ext: even more characters from second pattern
*/
class LiquidCrystal_I2C_ST7070_Ext : public LiquidCrystal_I2C {
  public:
    LiquidCrystal_I2C_ST7070_Ext(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) :
      LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows, convert_ST7070_ext) {}
};
