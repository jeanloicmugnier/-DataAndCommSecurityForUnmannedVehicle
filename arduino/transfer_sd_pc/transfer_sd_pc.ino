#include <SD.h>



//the hardware CS pin (10 on most Arduino boards,
//pin 4 as the CS pin
// 53 on the Mega) must be left as an output or the SD
// library functions will not work.

//#include "FileIO.h"
//include <stdio.h>


const int CSpin = 4;
String dataString =""; // holds the data to be written to the SD card
File sensorData;
File* pc_file;

void setup() {
   // Open serial communications
  //serial = new Serial( this, Serial.list()[0], 9600 );
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

  //opening file in pc to write
  //pc_file = fopen("pc_file","a");
}
void loop(){
  
}
void draw() {
    if (Serial.available() > 0 ) {
         String value = Serial.readString();
         if ( value != NULL ) {
              //fputs(value,pc_file);
         }
    }
}
/*
 * Aquire data from the sensors
 */

 
/* goes through the next file/directory
 *
 * print the tree
 *
 */
void printDirectory(File dir, int numTabs)
{
  while (true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      if (numTabs == 0)
        Serial.println("** Done **");
      return;
    }
    for (uint8_t i = 0; i < numTabs; i++)
      Serial.print('\t');
    Serial.print(entry.name());
    if (entry.isDirectory())
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

//SD.exists(filname)
//


