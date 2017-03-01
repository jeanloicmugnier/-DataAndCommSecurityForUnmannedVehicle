#include "changesecurity.h"

std::bitset<2> ChangeSecurity::get_sec(short level) {
    if (level == 0)return std::bitset<2>(0x00);
    if (level == 1)return std::bitset<2>(0x01);
    if (level == 2)return std::bitset<2>(0x10);
}

std::bitset<4> ChangeSecurity::get_sec_command_id() {
    return std::bitset<4>(0x0001);
}

