#include "command.h"

void Command::make_frame(Frame * f) {

}

int Command::get_bitset_size() {
    return this->bitset_size;
};

std::bitset<4> Command::get_command_id(std::string command) {
    if (!command.compare("MOVE")) {
        return std::bitset<4>(1);
    } else if (!command.compare("START RECORD")) {
        return std::bitset<4>(2);
    } else if (!command.compare("STOP RECORD")) {
        return std::bitset<4>(3);
    } else if (!command.compare("CHANGE SECURITY")) {
        return std::bitset<4>(4);
    } else {
        throw std::invalid_argument("wrong command string value: should be either MOVE, START RECORD, STOP RECORD, CHANGE SECURITY");
    }
}

