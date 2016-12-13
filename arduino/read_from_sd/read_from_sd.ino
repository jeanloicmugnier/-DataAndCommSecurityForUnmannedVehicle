

#include <FileIO.h>
#include <SD.h>

const int cs = 4;
String fileName = "textFile.txt";

void setup()
{
  Serial.begin(9600);
  



  Serial.print("Initializing card...");
  // make sure that the default chip select pin is declared OUTPUT
  
  pinMode(53, OUTPUT);
  
  // see if the card is present
  if (!SD.begin(cs)) 
  {
    Serial.println("Card failed to initialize, or not present");
  
    return;
  }
  Serial.println("card initialized.");
  
  // open the file named ourfile.txt
  
  SDLib::File myfile = SD.open(fileName );

  // if the file is available, read the file
  if (myfile) 
  {
    while (myfile.available())
    {
      Serial.write(myfile.read());
    }
    myfile.close();
  }  
  // if the file cannot be opened give error report
  else {
    Serial.println("error opening the text file");
  } 
}

void loop()
{
}
