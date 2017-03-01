/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ControlStation.h
 * Author: jeanloicm
 *
 * Created on February 20, 2017, 11:40 AM
 */

#ifndef CONTROLSTATION_H
#define CONTROLSTATION_H

#include "frame.h"
#include "hash.h"
#include <bitset>
#include <iostream>
#include "move.h"
#include "rover.h"
#include "changesecurity.h"
#include "record.h"
#include "sensors.h"

class ControlStation {
public:
    ControlStation(Rover* rover);
    ControlStation(const ControlStation& orig);
    virtual ~ControlStation();

    Frame* move_rover(std::bitset<3> direction, unsigned char time);
    Frame* change_security_rover(short level);
    Frame* start_recording(std::string sensor);
    Frame* stop_recording(std::string sensor);

    bool send(Command cmd);
    Rover* get_rover();

    short get_bitset_id_size();
    short get_bitset_cnt_size();
    short get_bitset_cmd_size();
    short get_bitset_parameters_size();
    short get_bitset_security_size();

    Frame* make_frame(Frame* frame);
    bitset<28> encrypt(Frame* frame);
    void print_frame(Frame* frame);
    bitset<128> hash(Frame* frame);
    bitset<128> hash_fake(Frame* frame);


private:
    const static short BITSET_ID_SIZE = 4;
    const static short BITSET_CNT_SIZE = 8;
    const static short BITSET_CMD_SIZE = 4;
    const static short BITSET_PARAMETERS_SIZE = 8;
    const static short BITSET_SECURITY_SIZE = 2;

    short get_cmd_size();
    Rover* rover;

    bitset<BITSET_ID_SIZE> cs_id;
    short security;
    bitset<BITSET_ID_SIZE> id;
    int counter;



};

#endif /* CONTROLSTATION_H */

