/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   sensor.cpp
 * Author: jeanloicm
 * 
 * Created on February 27, 2017, 11:14 AM
 */


#include "sensors.h"
#include <stdexcept>

Sensors::Sensors() {

}

std::bitset<4> Sensors::get_gps_id() {
    return this->gps_id;
}

std::bitset<4> Sensors::get_pressure_id() {
    return this->pressure_id;
}

std::bitset<4> Sensors::get_sensor_id(std::string sensor) {
    if (!sensor.compare("GPS")) {
        return std::bitset<4>(1);
    } else if (!sensor.compare("PRESSURE")) {
        return std::bitset<4>(2);
    } else {
        throw std::invalid_argument("wrong command string value: should be either GPS, PRESSURE");
    }
}
