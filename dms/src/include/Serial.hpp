#ifndef SERIAL_H
#define SERIAL_H

#include <string>

class Serial {
public :
    // member functions
    Serial(const tsu::config_map& init_map);
    virtual ~Serial();
    std::string Read ();
    void Write (std::string message);

private :
    // static properties
    std::string path_;      // location of device
    unsigned int baud_;     // serial transfer rate
    unsigned int context_;  // device file descriptor

private :
    // local functions
    std::string HexToString (std::string hex);
};

#endif // SERIAL_H
