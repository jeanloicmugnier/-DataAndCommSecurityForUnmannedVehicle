

#include <FileIO.h>
#include <SD.h>
#include <stdio.h>

class Writer{
  
  public:
    SDLib::File myfile;
    String fileName = "textFile.txt";
  public:
    Writer(){
      
    }
  public:
  void setup()
  {
 
    Serial.begin(9600);
    
    Serial.print("Initializing card...");
    
    // declare default CS pin as OUTPUT
     pinMode(53, OUTPUT);
     
    if (!SD.begin(4)) {
      Serial.println("initialization of the SD card failed!");
      return;
    }
    Serial.println("initialization of the SDcard is done.");
    
    myfile = SD.open(fileName, FILE_WRITE);
    
    
    if (myfile)
    {
      Serial.print("Writing to the text file...");
      myfile.println("Congratulations! You loose.");
    
      myfile.close(); // close the file:
      Serial.println("done closing.");
    } else
    {
      // if the file didn't open, report an error:
      Serial.println("error opening the text file!");
    }
    
    // re-open the text file for reading:
    myfile = SD.open("textFile.txt");
    if (myfile)
    {
      Serial.println("textFile.txt:");
      
      // read all the text written on the file
      while (myfile.available()) 
      {
        Serial.write(myfile.read());
      }
      // close the file:
      myfile.close();
    } else 
    {
      // if the file didn't open, report an error:
      Serial.println("error opening the text file!");
    }
  }

public:
void loop()
{
}
  public:
    void writeToFile(File file, String data){
      
    }
   public:
    void openFile(String file_name){
      File file = fopen(fila_name,a);
    }

};

int main()
{
Writer* w = new Writer();
w->setup();
}
