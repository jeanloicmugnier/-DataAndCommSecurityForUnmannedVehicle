using namespace std;

#include <cstdlib>
#include "crypto_stream_cpp.h"
#include <iostream>
class encryption{

	string msg = "hoje eu vou comer o seu lulu.";
	string key = "01234567891011121314151617181920"; // should have length 32
	string nounce="000000010000000100000001"; // should have length 24	

	/**
	 * Encryption and descryption
	 */
	string crypto_stream(string msg, string nounce, string key){

		string cipher = crypto_stream_xor(msg,nounce,key);		
	}
	
}