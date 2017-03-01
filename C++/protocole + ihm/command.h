/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   command.h
 * Author: jeanloicm
 *
 * Created on February 23, 2017, 10:13 AM
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <bitset>
#include <string.h>
#include "frame.h"

class Command {
public:
    static void make_frame(Frame * f);
    const static int bitset_size = 4;

    int get_bitset_size();
    static std::bitset<bitset_size> get_command_id(std::string command);
};

#endif /* COMMAND_H */

