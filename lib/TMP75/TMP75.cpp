// derived from https://github.com/parlotto/TMP75
#include "TMP75.h"

TMP75::TMP75(uint8_t address) :
_i2cAddress(address),
_isPresent(false)
{
}

int TMP75::begin(uint8_t configReg= )
{
  Wire.beginTransmission(_i2cAddress);
  Wire.write(TMP75_CONF_REG);
  Wire.write(TMP75_DEFAULT_CONFIG);
  if (!Wire.endTransmission()) {
    _isPresent = true;
    delay(100);
    // Setup Pointer Register to TEMP register
    Wire.beginTransmission(_i2cAddress);
    Wire.write(TMP75_TEMP_REG);
    return Wire.endTransmission();
  }
  else return 1;
}

// 12-bit signed data 1/16th degree C
int16_t TMP75::readTemperature()
{
  if (_isPresent) {
    // Setup Pointer Register to TEMP register
    // don't need to set pointer register, because we do it
    // in begin().. TMPx75 remembers the last value until it's
    // overwritten
    /*Wire.beginTransmission(_i2cAddress);
    Wire.write(TMP75_TEMP_REG);
    Wire.endTransmission();
    */
    // Read temperature value
    Wire.requestFrom(_i2cAddress, 2);
    int16_t t;
    t = Wire.read(); // high byte
    t <<= 8;
    t |= Wire.read();  // low byte
    // assume 12-bit mode
    t >>= 4; // unused bits are at bottom
    // t contains C * 16
    return (t * 10) / 16;  // return C*10
  }
  else return TEMPERATURE_NOT_INSTALLED;
}

#ifdef notusing
 void TMP75::setHighLimit( float highLimit )
 {
   int msb = highLimit ;
    int lsb = (highLimit - msb) * 256;
    Wire.beginTransmission(_i2cAddress);
    Wire.write(TMP75_THIGH_REG);
    Wire.write(msb);
    Wire.write(lsb & 0xF0);
    Wire.endTransmission();
   
 }
 
 void TMP75::setLowLimit( float lowLimit ){
    
  
    int msb = lowLimit ;
    int lsb = (lowLimit - msb) * 256;
    Wire.beginTransmission(_i2cAddress);
    Wire.write(TMP75_TLOW_REG);
    Wire.write(msb);
    Wire.write(lsb & 0xF0);
    Wire.endTransmission();
   
 }
 
#endif // notusing
