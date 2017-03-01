/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hash.cpp
 * Author: jeanloicm
 * 
 * Created on March 1, 2017, 1:57 PM
 */

#include "hash.h"

Hash::Hash(std::string in) {
    this->sip_hash = new SipHash_2_4();
    this->sip_hash->initFromPROGMEM(key);
    //    ulong l = in.to_ulong();
    const char *p = in.c_str();
    uint8_t *lol = (uint8_t *) p;
    sipHash.updateHash(*lol);
    this->sip_hash->finish();

}

Hash::Hash(const Hash& orig) {
}

uint8_t* Hash::get_key() {
    return this->key;
}

uint8_t * Hash::get_result() {
    return this->sip_hash->result;
}

Hash::~Hash() {
}

