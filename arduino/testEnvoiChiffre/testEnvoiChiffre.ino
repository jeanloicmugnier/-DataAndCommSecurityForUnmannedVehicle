#include "tweetnacl.c"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9,10);

char* msg = "Salut.";
char* key = "01234567891011121314151617181920"; // should have length 32 bytes
char* nounce="000000010000000100000002"; // should have length 24 bytes
char c[400];


void setup() {
  const byte rxAddr[6] = "00001";
    Serial.begin(9600);
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.setRetries(15, 15);
    radio.openWritingPipe(rxAddr);
  
    radio.stopListening();
    
    crypto_stream_xor(c,msg,strlen(msg),nounce,key);
}

void loop() {
  Serial.println(strlen(msg));
  Serial.println("coucou");
  Serial.println(strlen(c));
  radio.write(c, 128);
  Serial.println("debug");
  delay(1000);
}
