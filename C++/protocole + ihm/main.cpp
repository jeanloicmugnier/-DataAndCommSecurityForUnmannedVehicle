/* 
 * File:   main.cpp 
 * Author: jeanloicm
 *
 * Created on December 15, 2016, 9:00 PM
 */

#include <cstdlib>
//#include "crypto_stream_cpp.h"
#include <iostream>
#include <bitset>
#include <map>
#include "controlstation.h"
#include "move.h"
#include "rover.h"
#include "changesecurity.h"
#include "sensors.h"
//use vector<bool> instead

using namespace std;

/*bitset<192> str_to_bin(string str){
        int size = str.size();
        bitset<size*8> bit (str);
        return bit;
}*/

/*
 * bitset doc http://www.cplusplus.com/reference/bitset/bitset/bitset/
 * 
 */
int main(int argc, char** argv) {
    /*
         std::string msg = "The sun doesn't give light to the moon assuming The moon's going to owe it one";
         std::string key = "01234567891011121314151617181920"; // should have length 32 bytes
         std::string nounce="000000010000000100000002"; // should have length 24 bytes
         bitset<192> nouncebit (8);
         cout << "bitset: " << nouncebit  << " \n";
        std::string c;
        string dec;

        cout << "the size of the key is: " << key.size() << " bytes \n";
        cout << "the size of the nounce is: " << nounce.size() << " bytes \n";
	
        c = crypto_stream_xor(msg,nounce,key);
        dec = crypto_stream_xor(c,nounce,key);
        cout << "lloooool\n";
        //c = crypto_stream_xor(msg,nouce,key);

        cout << "the message is:' " << msg << " ' and it's size is: "<< msg.size() <<" \n";
        cout << "the cipher is:' " << c << " ' and it's size is: "<< c.size() <<" \n";
        cout << "the decrypted msg is:' " << dec << " ' and it's size is: "<< c.size() <<" \n";

	
        //Move move;
        //cout << move.get_bits() <<endl;
     */

    //    int nb = 32;
    //    bitset<8> b = bitset<8>(nb);
    //    cout << b << endl;
    //directions testing
    //    Direction* d = new Direction();
    //    std::bitset<3> forw = d->get_forward();
    //    std::bitset<3> right = d->get_right();
    //    std::bitset<3> back = d->get_backward();
    //    std::bitset<3> left = d->get_left();
    //    std::bitset<3> stop = d->get_stop();
    // sec levels
    //    std::bitset<2> sec0 = ChangeSecurity::get_sec(0);
    //    std::bitset<2> sec1 = ChangeSecurity::get_sec(1);
    //    std::bitset<2> sec2 = ChangeSecurity::get_sec(2);
    //sensors
    //    Sensors* s = new Sensors();
    //    cout << "lov" << endl;
    //    std::bitset<4> gps = s->get_gps_id();
    //    std::bitset<4> pressure = s->get_pressure_id();

    Rover* r = new Rover(std::bitset<4>(0x0001));
    //    cout << "lov1" << endl;
    ControlStation* cs = new ControlStation(r);
    //    cout << "lov2" << endl;
    //    Direction* dir = new Direction();
    //    cout << "lov3" << endl;
    //    bitset<3>* direc;
    //    cout << "move left : 0011" << endl;
    //    //    direc = (std::bitset<2>*) malloc(sizeof (dir->FORWARD));
    //
    //    // move
    //    Frame * f = cs->move_rover(Direction::get_directions("LEFT"), 1);
    //    f->print();
    //    cout << endl << endl;
    //    cout << "move right : 0001" << endl;
    //    f = cs->move_rover(Direction::get_directions("RIGHT"), 1);
    //    f->print();
    //    cout << "move forward : 0000 " << endl;
    //    cout << endl << endl;
    //    f = cs->move_rover(Direction::get_directions("FORWARD"), 1);
    //    f->print();
    //    cout << "mobe back : 0010" << endl;
    //    f = cs->move_rover(Direction::get_directions("BACKWARD"), 1);
    //    f->print();
    //    cout << "stop : 0100" << endl;
    //    f = cs->move_rover(Direction::get_directions("STOP"), 1);
    //    f->print();
    //    cout << endl << endl;
    //    //security
    //    f = cs->change_security_rover(0);
    //    f->print();
    //    cout << endl << endl;
    //    f = cs->change_security_rover(1);
    //    f->print();
    //    f = cs->change_security_rover(2);
    //    // sensors
    //    cout << "start record 2 gps 1" << endl;
    //    f = cs->start_recording("GPS");
    //    f->print();
    //    cout << "stop record 3 gps 1" << endl;
    //    f = cs->stop_recording("GPS");
    //    f->print();
    //    cout << "start record 2 pressure 2" << endl;
    //    f = cs->start_recording("PRESSURE");
    //    f->print();
    //    cout << "stopt record 3 pressure 2" << endl;
    Frame *f = cs->change_security_rover(1);
    FrameSec1 *sec1 = (FrameSec1*) f;
    //    sec1->print();
    cout << endl << endl;
    cout << endl << endl;
    *f = cs->change_security_rover(2);
    FrameSec2 *sec2 = (FrameSec2*) f;
    //    sec2->print();
    cout << endl << endl;
    //    bitset<28> lol = f->mount_frame();
    //    cout << lol << endl;
    return 0;
}

