#include "tweetnacl.c"
#include <SPI.h>
#include "RF24.h"
#include <nRF24L01.h>


RF24 radio(9,53);

const byte rxAddr[6] = "00001";
char* key = "01234567891011121314151617181920"; // should have length 32 bytes
char* nounce="000000010000000100000002"; // should have length 24 bytes

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.openReadingPipe(0, rxAddr);
  
   radio.startListening();
}

void loop() {
  if (radio.available())
  {
    char msg[400] = {0};
    radio.read(&msg, sizeof(msg));
    Serial.println("recu: " + (String)msg);
    //char* msg = "The sun doesn't give light to the moon assuming The moon's going to owe it one";
   
    char* c = malloc(strlen(msg));
    char* dec = malloc(strlen(msg));

    //Serial.write("the size of the key is:" + strlen(key) + "bytes \n");
    //Serial.print("the size of the nounce is: %lu bytes \n", strlen(nounce));

    long start = micros();
    crypto_stream_xor(c,msg,strlen(msg),nounce,key);
    long elapsed = micros()-start;
    crypto_stream_xor(dec, msg, strlen(msg),nounce,key);
    long elapsed2 = micros()-elapsed-start;
    Serial.println("Chiffrement : "+String(elapsed));
    Serial.println("Déchiffrement : "+String(elapsed2));

    //Serial.println("the message is:'" + (String)msg + "'");
    Serial.println("the decrypted msg is:'" + (String)dec + "'");
  } 
}



