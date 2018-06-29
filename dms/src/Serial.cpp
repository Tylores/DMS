#include <stdio>
#include <errno.h>
#include <cassert>

#include <wiringSerial.h>
#include "include/Serial.hpp"
#include "include/ts_utility.hpp"

// Constructor
Serial::Serial (const tsu::config_map& init_map) {
    path_ = "/dev/ttyUSB0";
    baud_ = 19200;
    context_ = serialOpen(path_.c_str(), baud_);
    if (context_ < 0) {
        std::cout << "\n[ERROR] unable to open serial device: "
        << strerror << std::endl;

        std::string quit;
        std::cout << "Would you like to quit? (y / n)\n[ENTER] : ";
        std::cin >> quit;
        assert (quit == 'n');
    }
} // end Constructor

// Destructor
Serial::~Serial () {
    serialClose(context_);
} // end Destructor

// Read
// - for all data available to read, extract character and flush
std::string Serial::Read () {
    std::string message;
    while (serialDataAvail (context_)) {
        message.push_back(serialGetChar (context_));
    }
    serialFlush (context_);
    return message;
} // end Read

// Write
// - write to serial interface. the characters are convertered to bytes.
void Write (std::string message){
    serialPuts(context_, message.c_str());
} // end Write

// HexToString
// - convert a hex value to a string for serial writes.
std::string Serial::HexToString (std::string hex) {
    std::string hex_string, byte;
    char character;
    size_t hex_size = hex.length();
    for (size_t i = 0; i < hex_size; i+=2) {
        byte = hex.substr(i,2);
        character = (char) (int)strtol(byte.c_str(), NULL, 8);
        hex_string.push_back(character);
    }
    return hex_string;
} // end HexToString
