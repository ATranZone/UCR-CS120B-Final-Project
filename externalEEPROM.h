#ifndef externalEEPROM_h
#define externalEEPROM_h
#include <Wire.h>
#include "Arduino.h"
#endif

#define storedAddress 0x50
class eepromLib {
  public:
  eepromLib();
  void write(byte writeValue, int address);
  byte read(int address);
};
