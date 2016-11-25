#include <Crypto.h>
#include <SHA256.h>
#include <string.h>

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  char *toHash = "abc";
  uint8_t hashed[32] = {0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
     0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
     0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
     0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad};
  SHA256 hash;
  
    size_t size = strlen(toHash);
    size_t posn, len;
    uint8_t value[32];

    size_t inc = strlen(toHash);
    (&hash)->reset();
    for (posn = 0; posn < size; posn += inc) {
        len = size - posn;
        if (len > inc)
            len = inc;
        (&hash)->update(toHash + posn, len);
    }
    (&hash)->finalize(value, sizeof(value));
    if (memcmp(value, hashed, sizeof(value)) != 0) {
      Serial.write("Non");
    } else {
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      Serial.write("OUI");
    }
}

// the loop function runs over and over again forever
void loop() {

  /*
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
  */
}
