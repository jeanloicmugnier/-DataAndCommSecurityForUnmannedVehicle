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
  for (int i = 3; i>0; i--) {
    delay(1000);
    Serial.print(F(" "));
    Serial.print(i);
  }
  Serial.println();
  Serial.println(F(" This SipHash test produces the results shown in https://131002.net/siphash/siphash24.c"));
  printKey((uint8_t*)key);
 
  char tmp[17];
 
    sipHash.initFromPROGMEM(key);
    float t = micros();
    for(int i = 0; i<500; i++) {
      sipHash.updateHash((byte)'a');
    }
    float elapsed = micros() - t;
    sipHash.finish(); // result in BigEndian format
    reverse64(sipHash.result); // go to little Endian
    hexToAscii(sipHash.result,8,tmp,17);
    Serial.print("Hash : ");
    Serial.println(tmp);
    //Serial.println("Temps écoulé pour hacher 16 octets : "+String(t2));
    //float onebyte = t2/16;
    //Serial.println("Temps pour hacher 1 octet : "+String(onebyte));
    Serial.println(elapsed);
    Serial.println("Octets hachés par seconde : "+String((sizeof(tmp)*500*1000000)/elapsed));
  
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






