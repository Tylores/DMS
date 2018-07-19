#ifndef WATERHEATER_H
#define WATERHEATER_H

// C++ includes
#include <string>
#include <map>

// Project includes
#include "universalcommunicationmodule.hpp"

class WaterHeater
{
public:
    WaterHeater();
    virtual ~WaterHeater();
    void Shed (int duration);
    void EndShed();
    void Absorb();
    void PrintProperties ();

private:
    // static properties should be where things like Vendor ID, Commodity,
    // Device Type, stuff like can be saved for easy access.
    std::map<std::string, std::string> static_properties_;
    unsigned int energy_take_;
    unsigned int tank_temperature_;
    unsigned int ambient_temperature_;

private :
    // class composition
    UniversalCommunicationModule UCM;
};

#endif // WATERHEATER_H
