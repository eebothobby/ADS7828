/*
  Arduino library for ADS7828, a 8-channel single-ended/4-channel differential
  12-bit ADC from TI with an I2C interface.
 */

#include "Arduino.h"
#include "ADS7828.h"

ADS7828::ADS7828() {
}

// i2caddr need only be the two address bits for the part (0 .. 3).
// twire defaults to a pointer to Wire, but it can be a pointer to a
// different TwoWire instance, such as Wire1, in a system with more than
// one i2c bus.
// By default PD1:PD0 are IREF_OFF_AD_ON

void ADS7828::begin(uint8_t i2caddr, TwoWire *twire) {
  _i2caddr = ADS7828_I2CADDR | (i2caddr & 0x3);
  _pdbits = IREF_OFF_AD_ON;
  _wire = twire;
}

// Set the PD1:PD0 bits
// pdval should be one of:
// PD_BTWN_CONV 0x0 Power down betweed A/D conversions
// IREF_OFF_AD_ON 0x04 Internal reference OFF, A/D converter ON (default)
// IREF_ON_AD_OFF 0x08 Internal reference ON, A/D conveter OFF
// IREF_ON_AD_ON 0x0C Internal reference ON, A/D converter ON
// 
void ADS7828::setpd(uint8_t pdval) {
  pdval = pdval & 0x0C;
  _pdbits = pdval;
}


// Common code to read 12-bit data from channel
uint16_t ADS7828::_readData(uint8_t channel, bool single) {
  uint8_t cmd = single? SINGLE_ENDED : DIFFERENTIAL;
  // force channel into 3 bits in case channel is out of range
  channel = channel & 0x7;
  uint8_t csel = (channel >> 1) | ((channel & 0x1) << 2);
  cmd = cmd | csel << 4 | _pdbits;
  _wire->beginTransmission(_i2caddr);
  _wire->write(cmd);
  _wire->endTransmission();

  _wire->requestFrom(_i2caddr, 2);
  while (_wire->available() < 2) {
    // Serial.println("Waiting");
  }
  uint16_t result = (_wire->read() & 0x0F) << 8;
  result = result + _wire->read();
  return result;
}

// read single-ended channel data
uint16_t ADS7828::read(uint8_t channel) {
  return _readData(channel, true);
}

// read differential channel data
uint16_t ADS7828::readdif(uint8_t channel) {
  return _readData(channel, false);
}
