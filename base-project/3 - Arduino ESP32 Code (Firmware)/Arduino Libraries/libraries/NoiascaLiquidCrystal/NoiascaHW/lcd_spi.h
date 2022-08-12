/*
   SPI 4bit variant
   
   open topics
   - backlight not tested with hardware so far
   
   2020-09-05
*/

#pragma once
#include <Arduino.h>
#include <NoiascaLiquidCrystal.h>
#include <SPI.h>

#if defined(ARDUINO) && ARDUINO < 100
#warning "Your Arduino IDE might be outdated and this library might not work correctly. Consider to update your Arduino IDE to 1.8.10 or newer"
#endif

// needed for the MCP23S08
//const byte chipAddr = 0x40;// 0 1 0 0 0 A1 A0 RW  (RW = 0 =write)
const byte ioDirReg = 0x00;  // When a bit is clear, the corresponding pin becomes an output.
const byte gpioReg = 0x09;

/*
   SPI base class
*/
class LiquidCrystal_SPI_base : public LiquidCrystal_dummy {
  public:
    LiquidCrystal_SPI_base(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t csPin) :
      LiquidCrystal_dummy(lcd_cols, lcd_rows),
      _Addr(lcd_Addr),
      csPin(csPin)
    {}
    
    // Turn the (optional) backlight off/on
    void noBacklight(void) {             // virtual?
      _backlightval = LCD_NOBACKLIGHT;
      expanderWrite(0);
    }
    
    void backlight(void) {
      _backlightval = LCD_BACKLIGHT;
      expanderWrite(0);
    }

    // alias for LCD API
    void setBacklight(uint8_t new_val) {
      if (new_val) 
        backlight();		  // turn backlight on
      else
        noBacklight();		// turn backlight off
    }

    bool isConnected() {
      return true;                         // dummy, assume success
    }

  protected:
    const uint8_t _Addr;                   // the address based on A0/A1
    void expanderWrite(uint8_t _data) {
      DEBUG_PRINTLN(F("SPI_base expanderWrite()"));
      digitalWrite(csPin, LOW);
      SPI.transfer(_Addr);
      SPI.transfer(gpioReg);
      SPI.transfer((int)(_data | _backlightval ));
      digitalWrite(csPin, HIGH);
    }

    void hwInit()
    {
      DEBUG_PRINTLN(F("SPI_base hwInit()"));
      pinMode(csPin, OUTPUT);
      delay(1);
      digitalWrite(csPin, LOW);
      SPI.transfer(_Addr);
      SPI.transfer(ioDirReg);
      SPI.transfer(0x00);                  // Set all pins to OUTPUT
      digitalWrite(csPin, HIGH);
      delay(1);
      digitalWrite(csPin, LOW);
      SPI.transfer(_Addr);
      SPI.transfer(gpioReg);
      SPI.transfer(0x00);                  // Set all pins LOW
      digitalWrite(csPin, HIGH);
    }

  private:
    const byte csPin;                      // CS pin to activate the chip
};

/*
   SPI default class with special character support
*/
class LiquidCrystal_SPI : public LiquidCrystal_SPI_base {
  protected:
    using CallBack = uint8_t (*)(uint32_t &special, uint8_t &value);
    CallBack funcPtr;  
    
  public:
    LiquidCrystal_SPI(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t csPin) :
      LiquidCrystal_SPI_base(lcd_Addr, lcd_cols, lcd_rows, csPin),
      funcPtr(convert)        // function pointer to default converter
      {}
      
    LiquidCrystal_SPI(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t csPin, CallBack funcPtr) :
      LiquidCrystal_SPI_base(lcd_Addr, lcd_cols, lcd_rows, csPin),
      funcPtr(funcPtr)        
      {}
   
    inline size_t write(uint8_t value) {
      DEBUG_PRINTLN(F("SPI write"));
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