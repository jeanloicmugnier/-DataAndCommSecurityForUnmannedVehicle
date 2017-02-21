#include "tweetnacl.c"

void setup() {
    Serial.begin(9600);
    char* msg = "The sun doesn't give light to the moon assuming The moon's going to owe it one";
    char* key = "01234567891011121314151617181920"; // should have length 32 bytes
    char* nounce="000000010000000100000002"; // should have length 24 bytes
   
    char* c = malloc(strlen(msg));
    char* dec = malloc(strlen(msg));

    //Serial.write("the size of the key is:" + strlen(key) + "bytes \n");
    //Serial.print("the size of the nounce is: %lu bytes \n", strlen(nounce));
    
    crypto_stream_xor(c,msg,strlen(msg),nounce,key);
    crypto_stream_xor(dec, c, strlen(c),nounce,key);

    Serial.print("the message is:'" + (String)msg + "'");
    Serial.print("the cipher is:'" + (String)c + "'");
    Serial.print("the decrypted msg is:'" + (String)dec + "'");
}

void loop() {
  
}



