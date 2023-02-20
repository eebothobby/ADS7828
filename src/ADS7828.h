/*
  Arduino library for ADS7828, a 8-channel single-ended/4-channel differential
  12-bit ADC from TI with an I2C interface.
  
 */
#ifndef ADS7828_h
#define ADS7828_h
#include "Arduino.h"
#include <Wire.h>

// Base I2C address, A1,A0 can give 0x48, 0x49, 0x4A, 0x4B
#define ADS7828_I2CADDR 0x48

// Definitions for the command byte.
// OR the various bits together to construct the byte
// MSB 7 SD bit
#define SINGLE_ENDED 0x80 // Single ended
#define DIFFERENTIAL 0x00 // Differential

// Bits 6:4 C2, C1, C0 Channel selectors
// No definitions needed since we will generate from channel
// and whether differential or single-ended

// Bits 3:2 PD1,PD0 Power down , refernece selection
#define PD_BTWN_CONV 0x0 // Power down betweed A/D conversions
#define IREF_OFF_AD_ON 0x04 // Internal reference OFF, A/D converter ON
#define IREF_ON_AD_OFF 0x08 // Internal reference ON, A/D conveter OFF
#define IREF_ON_AD_ON 0x0C // Internal reference ON, A/D converter ON
// LSB 1:0 not used XX

// Call Wire.begin() and optionally Wire.setClock() before using this class.

class ADS7828{
 public:
  ADS7828();

  // i2caddr need only be the two address bits for the part (0 .. 3).
  // The second argument (twire) is optional and defaults to a pointer to
  // the standard i2c instance Wire.
  // If there are multiple I2C channels, you can pass in a pointer to a
  // a non-standard one (e.g, Wire1)
  void begin(uint8_t i2caddr, TwoWire *twire = &Wire);
  
  // read single-ended channel data
  uint16_t read(uint8_t channel);

  // read differential channel data
  uint16_t readdif(uint8_t channel);

 private:
  TwoWire *_wire;
  // XXX I think _i2caddr ought to be uint8_t but that gives
  // a compiler warning because it's apparently declared an int in TwoWire
  int _i2caddr;
  uint16_t _readData(uint8_t channel, bool single);
};

#endif // #ifndef ADS7828_h
