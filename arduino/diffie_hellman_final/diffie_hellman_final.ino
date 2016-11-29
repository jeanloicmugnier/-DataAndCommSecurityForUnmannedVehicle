//#include <LiquidCrystal.h>
//#include "aes.h"

const long a = 6;
const long q = 761;

//LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

unsigned char Diffie_Hellman_num_exchange(){
  long X, Y, Y_other, K, temp;
  char Y_other_str[MOST_NO_OF_DIGITS + 1], incByte;
  X = random(2, q-1);
  Y = raiseto_mod(a, X, q);
  Serial.readBytes(Y_other_str, MOST_NO_OF_DIGITS);
  Serial.println(to_string(Y));
  Y_other_str[MOST_NO_OF_DIGITS] = '\0';
  Y_other = to_num(Y_other_str);
  K = raiseto_mod(Y_other, X, q);
  int diffie_hellman_num = K % 256;
  return (unsigned char) diffie_hellman_num;
}

void cycle_arduino_to_PC(unsigned char *AES_Key) {
  unsigned char ptext[100] = "North Korea invaded the United States today", *ctext;
  int FINAL_LENGTH = size_string(ptext);  
  ctext = ECB_AES_encrypt(ptext, AES_Key, FINAL_LENGTH);
  Serial.println(to_string(FINAL_LENGTH));
  for (int i = 0; i < FINAL_LENGTH; ++i) {
    Serial.println(ctext[i]);
  }
}

void cycle_PC_to_arduino(unsigned char* AES_Key) {
  unsigned char ctext[100], *ptext, AES_Key_uc[178];
  int length;
  char length_string[MOST_NO_OF_DIGITS + 1];
  Serial.readBytes(length_string, MOST_NO_OF_DIGITS);
  length_string[MOST_NO_OF_DIGITS] = '\0';
  length = to_num(length_string);
  int i;
  for (i = 0; i < length; ++i) {
    char num_str[4]; 
    Serial.readBytes(num_str, 3);
    num_str[3] = '\0';
    ctext[i] = to_num(num_str);
  }
  ctext[i] = '\0'; 
  ptext = ECB_AES_decrypt(ctext, AES_Key);
  delay(10000);  
}

void setup() {
  Serial.begin(115200);
  // synchronization
}

void loop() { 
  unsigned char AES_key[177];
  AES_key[176] = '\0';
  char mode[14];
  mode[13] = '\0';
  Serial.write("ready");
  Serial.readBytes(mode, 13);
  if (strcmp(mode, "PC_TO_ARDUINO") == 0) {
    //lcd.clear();
    for (int i = 0; i < 16; ++i) {
    AES_key[i] = Diffie_Hellman_num_exchange();
    }
    // read key starts again
    char indication[MOST_NO_OF_DIGITS + 1];
    Serial.readBytes(indication, MOST_NO_OF_DIGITS);
    indication[MOST_NO_OF_DIGITS] = '\0';
    while (strcmp(indication, "2&g&xb3leL") != 0) {
      for (int i = 0; i < 16; ++i) {
        AES_key[i] = Diffie_Hellman_num_exchange();
       }
      Serial.readBytes(indication, MOST_NO_OF_DIGITS);
    }
  cycle_PC_to_arduino(AES_key);
  }
  else if (strcmp(mode, "ARDUINO_TO_PC") == 0) {
    for (int i = 0; i < 16; ++i) {
    AES_key[i] = Diffie_Hellman_num_exchange();
    }
    cycle_arduino_to_PC(AES_key);
  }
  else {
    delay(10000);
  }
}
