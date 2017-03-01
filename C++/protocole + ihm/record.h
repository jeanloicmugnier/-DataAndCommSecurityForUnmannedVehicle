/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   record.h
 * Author: jeanloicm
 *
 * Created on February 27, 2017, 11:05 AM
 */

#ifndef RECORD_H
#define RECORD_H
#include <bitset>
#include "command.h"

class Record : Command {
private:
public:
    Record();
    std::bitset<4> get_start_command_id();
    std::bitset<4> get_stop_command_id();

};

#endif /* RECORD_H */

