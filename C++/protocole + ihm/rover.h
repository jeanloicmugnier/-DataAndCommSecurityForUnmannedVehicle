/* 
 * File:   rover.h
 * Author: jeanloicm
 *
 * Created on January 31, 2017, 4:59 PM
 */
//using namespace std;

#ifndef ROVER_H
#define ROVER_H

#include "frame.h"
#include "command.h"
#include "move.h"
#include <iostream>
#include <bitset>
#include <string>
#include <list>

class Rover {
public:
    Rover(std::bitset<4> id);
    Rover(const Rover& orig);
//    virtual ~Rover();


    //state
    //Command command;

    //list<Command> commands_historic;
    //methods
    void send(Frame frame); // send the Frame
    void make_frame(Command cmd); // make the frame to send

    /**
     * Move in the direction, four options in the direction enum in move class for time seconds
     * @param direction, enum in move.*, 
     * @param time, 0-255 seconds
     * @return 
     */
    void move(bitset<2> direction, unsigned char time);
    void move(bitset<2> direction);
    void move(Frame* frame, bitset<2>* direction, unsigned char time);
    /**
     * private method that impleme  nts the record actions
     * @param behave, start or stop
     * @param sensor_id, sensor id bitwise representation
     * @return 
     */
    void record(bitset<1> behave, bitset<4> sensor_id);
    void stop_recording(bitset<4> sensor_id);
    void start_recording(bitset<4> sensor_id);
    void change_security(bitset<2> security);
    void getInfo(bitset<4> sensor_id);
    void ack(bitset<8> command_id);
    void nack(bitset<8> command_id);
    void sync(bitset<8> time);
    void hash(Frame message);
    void encrypt(Frame message);
    void connect();
    void disconnect();
    void update_key();
    std::bitset<4> get_id();
    std::bitset<2> get_sec();

private:
    std::bitset<4> rover_id;
    std::bitset<2> security;
};

#endif /* ROVER_H */

