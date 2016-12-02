/*
 (c)2013 Forward Computing and Control Pty. Ltd. 
 www.forward.com.au
 This code may be freely used for both private and commercial use.
 Provide this copyright is maintained.
 */

#include "SipHash_2_4.h"
#include "HexConversionUtils.h"

const uint8_t key[] PROGMEM = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
                               0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50};

void setup() {
  //while(!Serial); // for Due
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // allow a little time to connect the serialMonitor before running the rest of the setup.
  for (int i = 10; i>0; i--) {
    delay(1000);
    Serial.print(F(" "));
    Serial.print(i);
  }
  Serial.println();
  Serial.println(F(" This SipHash test produces the results shown in https://131002.net/siphash/siphash24.c"));
  printKey((uint8_t*)key);
 
  char tmp[17];
 
  
    sipHash.initFromPROGMEM(key);
    sipHash.updateHash((byte)'a');
    sipHash.finish(); // result in BigEndian format
    reverse64(sipHash.result); // go to little Endian
    hexToAscii(sipHash.result,8,tmp,17);
    Serial.println(tmp);
  
}

void printKey(unsigned char PROGMEM *key) {
  Serial.print(F(" Key:"));
  unsigned char tmpKey[16];
  memcpy_P(tmpKey,key,16);
  char tmp[33];
  hexToAscii((const unsigned char*)tmpKey,16,tmp,33);
  Serial.println(tmp);
}

void loop() { }






