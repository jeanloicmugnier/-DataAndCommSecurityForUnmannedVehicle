#include <SD.h>

#include "tweetnacl.c"
#include <SPI.h>
#include "RF24.h"
#include <nRF24L01.h>

File file;
char* key = "01234567891011121314151617181920"; // should have length 32 bytes
char* nounce="000000010000000100000002"; // should have length 24 bytes

void setup() {
    Serial.begin(9600);
    if(!SD.begin(4)) {
      Serial.println("Initialisation carte échouée");
      return;
    }
    file = SD.open("GPS.txt", FILE_WRITE);
    char* msg = "28/2/2017 - 13:46:58 - 43.6156, 7.0724";
    int lengthMsg = strlen(msg) +1;
    char* c = (char*)malloc(lengthMsg);
    char* dec = (char*)malloc(lengthMsg);
    
    crypto_stream_xor(c,msg,lengthMsg,nounce,key);
    crypto_stream_xor(dec, c, lengthMsg,nounce,key);

    Serial.println("Message: '" + String(msg) + "'");
    Serial.println("Message chiffre: '" + String(c) + "'");
    Serial.println("Message dechiffre: '" + String(dec) + "'");
    file.print("Data: ");
    file.write(msg);
    file.println("\n");
    file.print("Cipher: ");
    file.write(c);
    file.println("\n");
    file.print("Deciphered: ");
    file.write(dec);
    file.println("\n");
    file.close();
    return;
}

void loop() {
/* code benchmark
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
  }  */
}



