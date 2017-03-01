#include "move.h"

Direction::Direction() {

}

std::bitset<3> Direction::get_forward() {
    return this->FORWARD;
}

std::bitset<3> Direction::get_right() {
    return this->RIGHT;
}

std::bitset<3> Direction::get_backward() {
    return this->BACKWARD;
}

std::bitset<3> Direction::get_left() {
    return this->LEFT;
}

std::bitset<3> Direction::get_stop() {
    return this->STOP;
}

std::bitset<3> Direction::get_directions(std::string direction) {
    if (!direction.compare("FORWARD")) {
        return std::bitset<3>(0);
    } else if (!direction.compare("RIGHT")) {
        return std::bitset<3> (1);
    } else if (!direction.compare("BACKWARD")) {
        return std::bitset<3>(2);
    } else if (!direction.compare("LEFT")) {
        return std::bitset<3>(3);
    } else if (!direction.compare("STOP")) {
        return std::bitset<3>(4);
    }
    throw std::invalid_argument("wrong direction string value: should be either FORWARD, RIGHT, LEFT or BACKWARD!");
}

bool Time::convert_time(unsigned char time) {
    //TODO
    return false;
}

Move::Move(bitset<3> direction, unsigned char time) {
    this->direction = direction;
    this->time = time;
}

Move::Move() {
    this->direction = std::bitset<3> (0x0);
    this->time = 0;
}

void Move::make_frame(Frame* frame) {
    //    frame->set_command(this->move_id);
    //frame->set_parameter(this->); TODO set the number the time bitset
}






