/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   frame.h
 * Author: jeanloicm
 *
 * Created on January 31, 2017, 5:01 PM
 */

#ifndef FRAME_H
#define FRAME_H

#include <bitset>
#include <iostream>
using namespace std;

class Frame {
private:
    static const short FRAME_SIZE = 28; // to be redefined
    std::bitset<4> src;
    std::bitset<4> dest;
    std::bitset<8> counter;
    std::bitset<4> command;
    std::bitset<8> parameter;

public:

    Frame(std::bitset<4> src, std::bitset<4> dest, std::bitset<8> counter, std::bitset<4> command, std::bitset<8> parameters);
    Frame(std::bitset<4> src, std::bitset<4> dest, std::bitset<8> counter);
    Frame();
    Frame(Frame* f);
    void print();
    void set_command(std::bitset<4> command);
    void set_parameter(std::bitset<8> parameters);
    bitset<FRAME_SIZE> mount_frame();
    std::bitset<4> get_src();
    std::bitset<4> get_dest();
    std::bitset<8> get_counter();
    std::bitset<4> get_command();
    std::bitset<8> get_parameter();
};

class FrameSec0 : public Frame {

    FrameSec0(std::bitset<4> src, std::bitset<4> dest, std::bitset<8> counter, std::bitset<4> command, std::bitset<8> parameters) :
    Frame(src, dest, counter, command, parameters) {
    }

};

class FrameSec1 : public Frame {
private:
    std::bitset<128> hash;
public:

    FrameSec1(std::bitset<4> src, std::bitset<4> dest, std::bitset<8> counter, std::bitset<4> data, std::bitset<8> parameters, std::bitset<128> hash) :
    Frame(src, dest, counter, data, parameters), hash(hash) {
        this->hash = hash;
    }

    bitset<128> get_hash();
    bitset<156> mount_frame();
    void print();

    //    FrameSec1(Frame* f, bitset<128> hash) : Frame(Frame* f) {
    //        this->hash = hash;
    //    }

};

class FrameSec2 : public Frame {
public:

    FrameSec2(bitset<4> src, bitset<4> dest, bitset<8> counter, bitset<4> data, bitset<8> parameters, bitset<128> hash) :
    Frame(src, dest, counter, data, parameters), hash(hash) {
        this->hash = hash;

    }

    void set_encrypted(bitset<28> encrypted);
    bitset<128> get_hash();
    bitset<28> get_encrypted();
    bitset<156> mount_frame();
    void print();
    //    FrameSec2(Frame* f, bitset<128> hash) : Frame(Frame* f) {
    //        this->hash = hash;
    //    }

private:
    std::bitset<128> hash;
    std::bitset<28> encrypted;

};



#endif /* FRAME_H */

