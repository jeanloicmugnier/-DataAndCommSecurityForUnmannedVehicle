#include <Crypto.h>
#include <AES.h>
#include <string.h>

/*
Writing Sensor Data to an SD card
//
This example shows how to write data
to an SD card using the SD library.
//
The circuit:
* SD card attached to SPI bus as follows:
** MOSI - pin 11
** MISO - pin 12
** CLK - pin 13
** CS - pin 10 Uno (53 on Mega)
Based on code by Tom Igoe
*/

#include "SD.h"
#include"SPI.h"


AES128 aes;
uint8_t buffer[16];
uint8_t key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};


//the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD
// library functions will not work.
const int CSpin = 10;
String dataString =""; // holds the data to be written to the SD card
File sensorData;


void setup() {
  // Open serial communications
  Serial.begin(9600);
  Serial.print("Initializing SD card...");
  pinMode(CSpin, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(CSpin)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  (&aes)->setKey(key,(&aes)->keySize());
}

void loop(){
  // build the data string
  dataString = "123;767543;108664";
  saveData(); // save to SD card
  delay(15000); // delay before next write to SD Card, adjust as required
  //readData();
  //delay(10000);
}

void saveData(){
 // if(SD.exists("data.csv")){ // check the card is still there
    // now append new data file
    sensorData = SD.open("data.csv", FILE_WRITE);
    if (sensorData){
      (&aes)->encryptBlock(buffer,reinterpret_cast<const uint8_t*>(dataString.c_str()));
      sensorData.println((char*)buffer);
      sensorData.close(); // close the file
    }
    else{
      Serial.println("Error writing to file !");
    }
      
}

void readData() {
  sensorData = SD.open("data.csv", FILE_READ);
  if (sensorData) {
    Serial.println("Lu :" + sensorData.read());
  }
}

