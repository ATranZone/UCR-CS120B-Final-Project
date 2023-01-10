#include "externalEEPROM.h"
eepromLib::eepromLib(){}

void eepromLib::write (byte writeValue, int address ) 
{
  Wire.beginTransmission(storedAddress); //queue bytes for transmission for the write() function
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.write(writeValue);
  Wire.endTransmission(); //ends transmission and transmits the bytes that were queued with write()
}

byte eepromLib::read(int address ) 
{
  byte readData = 0;
  Wire.beginTransmission(storedAddress);
  Wire.write((int)(address >> 8));   
  Wire.write((int)(address & 0xFF)); 
  Wire.endTransmission();  
  Wire.requestFrom(storedAddress, 1);
  if(Wire.available()){  
    readData =  Wire.read();
  }
  return readData;
}
