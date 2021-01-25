// derived from https://github.com/parlotto/TMP75
#ifndef TMP75_H
#define TMP75_H

#include <Wire.h>
#include <Arduino.h>

#ifndef TEMPERATURE_NOT_INSTALLED
#define TEMPERATURE_NOT_INSTALLED -2560
#endif


//#define TMP75_DEFAULT_ADDR 0x48 // address with A0=A1=A2=GND
#define TMP75_DEFAULT_ADDR 0x37

#define TMP75_DEFAULT_CONFIG 0x60 // 12 bits , 0 fault queue, ALERT low polarity, comparator mode  

// registers pointers
#define TMP75_TEMP_REG 0
#define TMP75_CONF_REG 1
#define TMP75_TLOW_REG 2
#define TMP75_THIGH_REG 3


class TMP75 {
  uint8_t _i2cAddress;
  bool _isPresent;
 public :
  TMP75(uint8_t address=TMP75_DEFAULT_ADDR);
  int begin();
  int16_t readC16(); // returns C*16. To convert to C*10 = (t*10)/16
  void setHighLimit( float highLimit );
  void setLowLimit(  float lowLimit );
};

#endif
