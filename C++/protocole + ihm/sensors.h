/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sensors.h
 * Author: jeanloicm
 *
 * Created on February 27, 2017, 11:09 AM
 */

#ifndef SENSORS_H
#define SENSORS_H

#include <bitset>
#include <list>
#include <string.h>
#include <iostream>

class Sensors {
private:
    std::bitset<4> gps_id = std::bitset<4>(1);
    std::bitset<4> pressure_id = std::bitset<4>(2);

public:
    Sensors();
    static std::bitset<4> get_sensor_id(std::string sensor);
    std::bitset<4> get_gps_id();
    std::bitset<4> get_pressure_id();
};

#endif /* SENSORS_H */

