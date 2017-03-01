/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   changesecurity.h
 * Author: jeanloicm
 *
 * Created on February 27, 2017, 10:56 AM
 */

#ifndef CHANGESECURITY_H
#define CHANGESECURITY_H

#include <bitset>
#include "command.h"

class ChangeSecurity : Command {
private:
    const std::bitset<2> sec0 = std::bitset<2>(0x00);
    const std::bitset<2> sec1 = std::bitset<2>(0x01);
    const std::bitset<2> sec2 = std::bitset<2>(0x10);
public:
    ChangeSecurity();
    static std::bitset<2> get_sec(short level);
    static std::bitset<4> get_sec_command_id();

};


#endif /* CHANGESECURITY_H */

