// C++ includes
#include <iostream>

// Project includes
#include "waterheater.hpp"

WaterHeater::WaterHeater (){
    std::map<std::string,std::string> reply = UCM.GetInfo();
    // this is ranged loop based on the reply map. i parse it and add each
    // element to the static properties member variable for easy access.
    for (const auto &idx : reply){
        static_properties_[idx.first] = idx.second;
    }
}  // end Constructor

WaterHeater::~WaterHeater (){

}  // end Destructor

void WaterHeater::Shed (int duration){
    std::string response = UCM.Shed(duration);
    std::cout << "Shed response: " << response << std::endl;
}  // end Shed

void WaterHeater::EndShed (){

}
void WaterHeater::Absorb (){

}  // end Absorb

void WaterHeater::PrintProperties (){
    std::cout << "\n***Water Heater Properties***\n" << std::endl;
    for (const auto &idx : static_properties_) {
        std::cout << "[KEY]\t" << idx.first
        << "\n[VALUE]\t" << idx.second << "\n\n";
    }
}  //end Print Properties
