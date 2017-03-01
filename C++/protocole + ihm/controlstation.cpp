/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ControlStation.cpp
 * Author: jeanloicm
 * 
 * Created on February 20, 2017, 11:40 AM
 */

#include "controlstation.h"
#include "record.h"
#include "sensors.h"
#include "changesecurity.h"
#include "record.h"

ControlStation::ControlStation(Rover* rover) {
    this->rover = rover;
    this->id = bitset<4>(1);
    this->security = 0;
}

ControlStation::ControlStation(const ControlStation& orig) {
}

ControlStation::~ControlStation() {
}

Rover* ControlStation::get_rover() {
    return this->rover;
}

//#define IS_INTEGRAL(T) typename std::enable_if< std::is_integral<T>::value >::type* = 0
//
//template<class T>
//std::string integral_to_binary_string(T byte, IS_INTEGRAL(T))
//{
//    std::bitset<sizeof(T) * CHAR_BIT> bs(byte);
//    return bs.to_string();
//}

Frame* ControlStation::move_rover(std::bitset<3> direction, unsigned char time) {
    //    Rover rover = get_rover();
    std::bitset<4> move_id = Command::get_command_id("MOVE");
    std::bitset<4> rover_id = this->get_rover()->get_id();
    std::bitset<8> param = std::bitset<8> (direction.to_ulong());
    std::bitset<8> counter = std::bitset<8> (this->counter);
    Frame* f = new Frame(rover_id, this->cs_id, counter, move_id, param);
    make_frame(f);
    this->counter++;
    return f;
}

bitset<128> ControlStation::hash_fake(Frame* frame) {
    bitset<28> f = frame->mount_frame();
    Hash* hash = new Hash(f.to_string());
    uint8_t * hashed = hash->get_result();
    bitset<128> hashed_bitset = bitset<128>(*hashed);
    //    cout << "hashed: " << hashed_bitset << " " << hashed_bitset.size() << endl;
    return hashed_bitset;
}

/**
 * Hashing using only bits
 * @param frame
 * @return 
 */
bitset<128> ControlStation::hash(Frame* frame) {
    bitset<28> f = frame->mount_frame();
    Hash* hash = new Hash(f.to_string());
    uint8_t * hashed = hash->get_result();
    bitset<128> hashed_bitset = bitset<128>(*hashed);
    //    cout << "hashed: " << hashed_bitset << " " << hashed_bitset.size() << endl;
    return hashed_bitset;
}

short ControlStation::get_cmd_size() {
    return this->BITSET_CMD_SIZE;
}

Frame* ControlStation::change_security_rover(short level) {
    //    std::bitset<2> sec_level_param = ChangeSecurity::get_sec(level);
    if (0 <= level && level < 3) {
        this->security = level;
    } else {
        throw std::invalid_argument("wrong security level requested: only 0, 1 and 2.");
    }
    std::bitset<8> param = std::bitset<8>(level);
    std::bitset<4> sec_command_id = Command::get_command_id("CHANGE SECURITY");
    std::bitset<8> counter = std::bitset<8> (this->counter);

    Frame* f = new Frame(this->get_rover()->get_id(), this->cs_id, counter, sec_command_id, param);
    make_frame(f);
    this->counter++;

    return f;
}

Frame* ControlStation::start_recording(std::string sensor) {
    std::bitset<8> param = std::bitset<8>(Sensors::get_sensor_id(sensor).to_ulong());
    std::bitset<8> counter = std::bitset<8> (this->counter);
    Frame* f = new Frame(this->get_rover()->get_id(), this->cs_id, counter, Command::get_command_id("START RECORD"), param);
    make_frame(f);
    this->counter++;

    return f;
}

Frame* ControlStation::stop_recording(std::string sensor) {
    std::bitset<8> param = std::bitset<8>(Sensors::get_sensor_id(sensor).to_ulong());
    std::bitset<8> counter = std::bitset<8> (this->counter);
    Frame* f = new Frame(this->get_rover()->get_id(), this->cs_id, counter, Command::get_command_id("STOP RECORD"), param);
    make_frame(f);
    this->counter++;

    return f;
}

void ControlStation::print_frame(Frame* frame) {

}

Frame* ControlStation::make_frame(Frame* frame) {
    if (this->security == 0) {
        frame->print();
        return frame;
    }
    // make hash
    std::bitset<128> hash = this->hash(frame);
    if (this->security == 1) {
        FrameSec1* f1 = new FrameSec1(frame->get_src(), frame->get_dest(), frame->get_counter(), frame->get_command(), frame->get_parameter(), hash);
        f1->print();
        return f1;
    } else if (this->security == 2) {
        bitset<28> encrypted = this->encrypt(frame);
        FrameSec2* f2 = new FrameSec2(frame->get_src(), frame->get_dest(), frame->get_counter(), frame->get_command(), frame->get_parameter(), hash);
        f2->print();
        return f2;
    }
}

bitset<28> ControlStation::encrypt(Frame* frame) {

}

short ControlStation::get_bitset_id_size() {
    return this->BITSET_ID_SIZE;
}

short ControlStation::get_bitset_cnt_size() {
    return this->BITSET_CNT_SIZE;
}

short ControlStation::get_bitset_cmd_size() {
    return this->BITSET_CMD_SIZE;
}

short ControlStation::get_bitset_parameters_size() {
    return this->BITSET_PARAMETERS_SIZE;
}

short ControlStation::get_bitset_security_size() {
    return this->BITSET_SECURITY_SIZE;
}
