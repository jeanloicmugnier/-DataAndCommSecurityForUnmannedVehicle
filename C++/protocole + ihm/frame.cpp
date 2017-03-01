#include "frame.h"

Frame::Frame(std::bitset<4> src, std::bitset<4> dest, std::bitset<8> counter, std::bitset<4> command, std::bitset<8> parameters) {
    this->src = src;
    this->dest = dest;
    this->counter = counter;
    this->command = command;
    this->parameter = parameters;
};

Frame::Frame(std::bitset<4> src, std::bitset<4> dest, std::bitset<8> counter) {
    this->src = src;
    this->dest = dest;
    this->counter = counter;
    this->command = bitset<4>(0x0);
    this->parameter = bitset<8>(0x0);
};

Frame::Frame() {
    this->src = std::bitset<4>(0x0);
    this->dest = std::bitset<4>(0x0);
    this->counter = std::bitset<8> (0x0);
    this->command = std::bitset<4> (0x0);
    this->parameter = std::bitset<8> (0x0);
};

Frame::Frame(Frame* f) {
    this->src = f->get_src();
    this->dest = f->get_dest();
    this->counter = f->get_counter();
    this->command = f->get_command();
    this->parameter = f->get_parameter();
};

std::bitset<4> Frame::get_src() {
    return this->src;
}

std::bitset<4> Frame::get_dest() {
    return this->dest;
}

std::bitset<8> Frame::get_counter() {
    return this->counter;
}

std::bitset<8> Frame::get_parameter() {
    return this->parameter;
}

std::bitset<4> Frame::get_command() {
    return this->command;
}

bitset<28> Frame::mount_frame() {
    std::string all = this->get_src().to_string()
            + this->get_dest().to_string()
            + this->get_counter().to_string()
            + this->get_command().to_string()
            + this->get_parameter().to_string();
    return bitset<28>(all);
}

void FrameSec1::print() {
    std::cout << "src id :\t " << this->get_src() << endl;
    std::cout << "dst id :\t " << this->get_dest() << endl;
    std::cout << "counter:\t " << this->get_counter() << endl;
    std::cout << "command:\t " << this->get_command() << endl;
    std::cout << "params :\t " << this->get_parameter() << endl;
    std::cout << "hash   :\t " << this->get_hash() << endl;
}

void Frame::print() {
    std::cout << "src id  :\t " << this->src << endl;
    std::cout << "dst id  :\t " << this->dest << endl;
    std::cout << "counter :\t " << this->counter << endl;
    std::cout << "command :\t " << this->command << endl;
    std::cout << "params  :\t " << this->parameter << endl;
}

void Frame::set_command(std::bitset<4> command) {
    this->command = command;
}

void Frame::set_parameter(std::bitset<8> parameters) {
    this->parameter = parameters;
}

bitset<156> FrameSec1::mount_frame() {
    std::string all = this->get_src().to_string()
            + this->get_dest().to_string()
            + this->get_counter().to_string()
            + this->get_command().to_string()
            + this->get_parameter().to_string()
            + this->get_hash().to_string();
    return bitset<156>(all);
}

bitset<128> FrameSec1::get_hash() {
    return this->hash;
}

bitset<128> FrameSec2::get_hash() {
    return this->hash;
}

void FrameSec2::set_encrypted(bitset<28> encrypted) {
    this->encrypted = encrypted;
}

bitset<28> FrameSec2::get_encrypted() {
    return this->encrypted;
}

bitset<156> FrameSec2::mount_frame() {
    bitset<156> new_frame = bitset<156>(this->get_encrypted().to_string() + this->get_hash().to_string());
    return new_frame;
}

void FrameSec2::print() {
    std::cout << "decrypted frame:  :\t "
            << this->get_src()
            << this->get_dest()
            << this->get_counter()
            << this->get_command()
            << this->get_parameter()
            << endl;
    std::cout << "encrypted frame:  :\t " << get_encrypted() << endl;
    std::cout << "hash  :\t " << this->get_hash() << endl;
}