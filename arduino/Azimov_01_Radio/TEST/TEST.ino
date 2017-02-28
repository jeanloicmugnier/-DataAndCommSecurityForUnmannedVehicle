#include <SoftwareSerial.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <nRF24L01.h>
#include "RF24.h"
#include "tweetnacl.c"

File file;
char* key = "01234567891011121314151617181920";
char* nounce = "000000010000000100000002";
int count = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== Init ===");
  // Initialisation de la carte SD
  pinMode(53, OUTPUT);
  //digitalWrite(10, HIGH);
  Serial.println("Initialisation de la carte SD...");
  if (!SD.begin(4)) {
    Serial.println("initialisation echouee !");
    return;
  }
  file = SD.open("tst.txt", FILE_WRITE);
}

void loop() {
  while(count++ < 20) {
    if(file) {
      Serial.println("--- Boucle "+String(count)+" ---");
      char* capture = "tst";
      Serial.println("Capture : "+String(capture));
      file.write(capture);
      char* cipher = malloc(strlen(capture));
      char* dec = malloc(strlen(capture));
      long start = micros();
      crypto_stream_xor(cipher,capture,strlen(capture),nounce,key);
      float elapsed = micros()-start;
      crypto_stream_xor(dec, cipher, strlen(cipher),nounce,key);
      float elapsed2 = micros()-elapsed-start;
      Serial.print("Chiffrement : "+String(elapsed/(sizeof(capture)))+" us/octet, ");
      Serial.println("Déchiffrement : "+String(elapsed2/(sizeof(capture)))+" us/octet");
      Serial.println("Cipher : "+String(cipher));
      Serial.println("Deciphered : "+String(dec));
      file.write(cipher);
      file.write(dec);
      free(&cipher);
      free(&dec);
      free(&capture);
      Serial.println("Fin boucle "+String(count));
    } else {
      Serial.println("Fichier non ouvert");
    }
    delay(1000);
  }
  file.close();
  Serial.println("Fichier fermé !");
}
