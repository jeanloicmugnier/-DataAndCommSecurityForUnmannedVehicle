/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jeanloicm
 *
 * Created on December 15, 2016, 9:00 PM
 */



#include <cstdlib>
#include "crypto_stream_cpp.h"
#include <iostream>
#include <bitset>
#include <map>
//use vector<bool> instead

using namespace std;

/*bitset<192> str_to_bin(string str){
	int size = str.size();
	bitset<size*8> bit (str);
	return bit;
}*/

/*
 * bitset doc http://www.cplusplus.com/reference/bitset/bitset/bitset/
 * 
 */
int main(int argc, char** argv) {

	 std::string msg = "The sun doesn't give light to the moon assuming The moon's going to owe it one";
	 std::string key = "01234567891011121314151617181920"; // should have length 32 bytes
	 std::string nounce="000000010000000100000002"; // should have length 24 bytes
	 bitset<192> nouncebit (8);
	 cout << "bitset: " << nouncebit  << " \n";
	std::string c;
	string dec;

	cout << "the size of the key is: " << key.size() << " bytes \n";
	cout << "the size of the nounce is: " << nounce.size() << " bytes \n";
	
	c = crypto_stream_xor(msg,nounce,key);
	dec = crypto_stream_xor(c,nounce,key);
	cout << "lloooool\n";
	//c = crypto_stream_xor(msg,nouce,key);

	cout << "the message is:' " << msg << " ' and it's size is: "<< msg.size() <<" \n";
	cout << "the cipher is:' " << c << " ' and it's size is: "<< c.size() <<" \n";
	cout << "the decrypted msg is:' " << dec << " ' and it's size is: "<< c.size() <<" \n";

	
	//Move move;
	//cout << move.get_bits() <<endl;

    return 0;
}

