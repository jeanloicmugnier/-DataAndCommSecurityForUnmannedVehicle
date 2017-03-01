
/* 
 * File:   rover.cpp
 * Author: jeanloicm
 * 
 * Created on January 31, 2017, 4:59 PM
 */

#include "rover.h"

Rover::Rover(std::bitset<4> id) {
    this->rover_id = id;
}

std::bitset<2> Rover::get_sec() {
    return this->security;
}

void Rover::make_frame(Command cmd) {
    // test the class of the command with switch case
    // convert it when found
    // get the frame from the class
    // apply the security according to the security level
    // call the Uno interface to send it to the rover.

}

void Rover::move(Frame* frame, bitset<2>* direction, unsigned char time) {
    //make log;
}

void Rover::move(bitset<2> direction, unsigned char time) {
    //Frame * frame = new Frame(this->id, this->rover_id, this->counter);
    //    Move m = new Move(direction, time);
    //    m.make_frame()
    //    id = this->rover_id;
    //    rover_id = this->rover_id;
    //    Frame f = Move.make_frame();
    //    this->send(f);
}

void Rover::move(bitset<2> direction) {
    unsigned char time = 10;
    move(direction, time);
}

/**
 * Send the Frame to the Uno, for the uno to send it to the Rover via the link radio rf24 
 * @param frame
 * @return 
 */
void Rover::send(Frame frame) {

}

/**
 * Change security to one of the security class.
 * if the security is not good, make a retry
 * @param security, one of the 3 
 * @return 
 */
void Rover::change_security(bitset<2> seclevel) {
    this->security = seclevel;
    //    Frame f;
    //    Move::make_frame();
    //create the frame for change security;
    //    this->send(f);

}

/**
 * private method that implements the record actions
 * @param behave, start or stop
 * @param sensor_id, sensor id bitwise representation
 * @return 
 */
void Rover::record(bitset<1> behave, bitset<4> sensor_id) {

}

/**
 * make the start recording 
 * @param behave, start, stop, from class recording enum
 * @param sensor_id, id of the sensor, from the enum in the list of sensors
 * @return 
 */
void Rover::start_recording(bitset<4> sensor_id) {
    //TODO

}

/**
 * stop recording of the device with id sensor_id
 * @param sensor_id, id of the sensor, from the enum in the list of sensors
 * @return 
 */
void Rover::stop_recording(bitset<4> sensor_id) {
    //TODO

}

std::bitset<4> Rover::get_id() {
    return this->rover_id;
}

/*
 
 
 
IMPLEMENT LATER 
 
 
 
 
 */

/**
 * Sends a nack, to tell that there is an error.
 * @param command_id
 * @return 
 */
void Rover::nack(bitset<8> command_id) {

}

/**
 * Sends an ack to the Rover telling the 
 * @param command_id, identification of the command
 * @return 
 */
void Rover::ack(bitset<8> command_id) {

}

/**
 * hashin the message of size x. and give an output of fixed size. Should use our chosen hash emplementation.
 * 
 * @return 
 */
void Rover::hash(Frame message) {

}

/**
 * Allows to update the Rover clock according to the time in the control station.
 * THis method should be called periodicly to prevent phase shift
 * TODO format the time an a bitset -> number of bits to represent time.
 * @param time, current time in the control station.
 * @return 
 */
void Rover::sync(bitset<8> time) {

}

/**
 * get the information about the data capted by the Rover.
 * @param sensor_id, identificaiton of the sensor in bits, use enum 
 * @return 
 */
void Rover::getInfo(bitset<4> sensor_id) {

}