/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   move.h
 * Author: jeanloicm
 *
 * Created on February 22, 2017, 5:27 PM
 */

#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <map>
#include <bitset>
#include <cassert>
#include <stdexcept>
#include "command.h"
using namespace std;

struct Comparer {

    bool operator()(const bitset<8> &b1, const bitset<8> &b2) const {
        return b1.to_ulong() < b2.to_ulong();
    }
};

class Direction {
public:

    Direction();
    const std::bitset<3> FORWARD = std::bitset<3>(0x000);
    const std::bitset<3> RIGHT = std::bitset<3> (0x001);
    const std::bitset<3> LEFT = std::bitset<3>(0x010);
    const std::bitset<3> BACKWARD = std::bitset<3>(0x011);
    const std::bitset<3> STOP = std::bitset<3>(0x100);
    //    map<string, bitset <2>, Comparer> directions = {
    //        {"FORWARD", 0x00},
    //        {"RIGHT", 0x01},
    //        {"LEFT", 0x10},
    //        {"BACKWARD", 0x11}
    //    };
    bitset<3> get_forward();
    bitset<3> get_stop();
    bitset<3> get_right();
    bitset<3> get_left();
    bitset<3> get_backward();
    static bitset<3> get_directions(string direction);
};

class Time {
public:
    bool convert_time(unsigned char time); // 

};

class Move : Command {
public:
    std::bitset<3> direction;
    unsigned char time; // in seconds

    Move(bitset<3> direction, unsigned char time);
    Move();
    static void make_frame(Frame *frame);

    //    static void make_frame(Frame * frame, bitset<4> move_id, bitset<8> parameter);

    bitset<4> get_move_id();

};




#endif /* MOVE_H */

