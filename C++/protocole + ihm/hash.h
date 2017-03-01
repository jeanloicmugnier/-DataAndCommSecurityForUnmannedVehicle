/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hash.h
 * Author: jeanloicm
 *
 * Created on March 1, 2017, 1:57 PM
 */

#ifndef HASH_H
#define HASH_H

#include <cstdint>
#include "sipHash_2_4.h"
#include <bitset>

class Hash {
public:

    Hash(std::string word);
    Hash(const Hash& orig);
    uint8_t * get_result();
    virtual ~Hash();
    uint8_t* get_key();
private:
    uint8_t key[16] = {0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50}; //shouldnt be hardcorded. use creation random!
    SipHash_2_4* sip_hash;
};

#endif /* HASH_H */

