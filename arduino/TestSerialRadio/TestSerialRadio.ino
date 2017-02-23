#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10);

void setup() {
    const byte rxAddr[6] = "00001";
    const byte txAddr[6] = "00002";
    Serial.begin(9600);
    radio.begin();
    radio.setPALevel(RF24_PA_MIN);
    radio.setRetries(15, 15);
    radio.openWritingPipe(rxAddr);
    radio.openReadingPipe(1, txAddr);
}

char cmd;
char ack[3];
void loop() {
  radio.stopListening();
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    cmd = Serial.read();
  
    // say what you got:
    Serial.print("I send: ");
    Serial.println(cmd);
    Serial.println(sizeof(ack));
    bool work = radio.write(&cmd,sizeof(cmd));

    Serial.println((work) ? "oui" : "non");
    radio.startListening();
    while (!radio.available()) {
      Serial.println("wait");  
    }
    radio.read(&ack,sizeof(ack));
    Serial.print("Received: ");
    Serial.println((String)ack);
    String str_ack = String(ack);
    str_ack.trim();
    Serial.println(str_ack.equalsIgnoreCase("ACK"));
    Serial.println(str_ack);
   }
}

/*void sendCommand() {
  char cmd;
  if (Serial.available() > 0) {
      // read the incoming byte:
      cmd = Serial.read();
      Serial.print("Envoyé: "+cmd);
      radio.write(&cmd,1);
  }
}

void readAnswer() {

  if (radio.available()) {
    char msg[32] = {0};
    radio.read(&msg, sizeof(msg));
    Serial.println("Recu: "+String(msg));
  }
  
}*/

