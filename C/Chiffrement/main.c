    #include "crypto_stream.h"

int main(int argc, char** argv) {

    char* msg = "The sun doesn't give light to the moon assuming The moon's going to owe it one";
    char* key = "01234567891011121314151617181920"; // should have length 32 bytes
    char* nounce="000000010000000100000002"; // should have length 24 bytes
     /*bitset<192> nouncebit (8);
     cout << "bitset: " << nouncebit  << " \n";*/
    char* c = malloc(strlen(msg));
    char* dec = malloc(strlen(msg));

    printf("the size of the key is: %lu bytes \n", strlen(key));
    printf("the size of the nounce is: %lu bytes \n", strlen(nounce));
    
    //crypto_stream_xor(c,msg,strlen(msg),nounce,key);
    c = "�<Y��Z�ΰА���a5(����H>�k���nI�Y����`R8*�����f����
                                                                      T!�?��ja+��!�Rݗ�J\0";
    printf("coucou: %lu \n",strlen(c));
    crypto_stream_xor(dec, c, strlen(c),nounce,key);

    printf("the message is:' %s ' and it's size is %lu \n", msg, strlen(msg));
    printf("the cipher is:' %s ' and it's size is: %lu \n", c, strlen(c));
    printf("the decrypted msg is:' %s ' and it's size is: %lu \n", dec, strlen(dec));

    
    //Move move;
    //cout << move.get_bits() <<endl;

    return 0;
}

