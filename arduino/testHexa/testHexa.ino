#include "SipHash_2_4.h"
#include "HexConversionUtils.h"

const uint8_t key[] PROGMEM = {0x41, 0x42,0x43,0x44,0x45,0x46,0x47,0x48,
                                    0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,0x50};
                                    
void setup() {
    Serial.begin(9600);

  /*for (int i=10; i>0; i--) {
    delay(1000);
    Serial.print(F(" "));
    Serial.print(i);
  }*/
    
    Serial.println();
    byte command[16] = {0x00,0x00,0x00,0x02,0xce,0x19,0xbe,0xb2,0xa0,0x29,0x30};
    //Serial.readBytes(command, 11);
    char tmp2[23];
    hexToAscii(command,11,tmp2,23);
    Serial.println(tmp2);
    
    sipHash.initFromPROGMEM(key);
    for (int i = 0; i < 3; i++) {
      Serial.print(command[i] + " ");
      sipHash.updateHash(command[i]);
    }
    Serial.println();
    sipHash.finish(); // result in BigEndian format
    reverse64(sipHash.result); // go to little Endian
    Serial.print("Result: ");
    char tmp[17];
    hexToAscii(sipHash.result,8,tmp,17);
    Serial.println(tmp);

    int n = memcmp(command+3, sipHash.result, 8);
    Serial.print("Comparaison: ");
    Serial.println(n);
   
 
}

void loop() {
  // put your main code here, to run repeatedly:

}
