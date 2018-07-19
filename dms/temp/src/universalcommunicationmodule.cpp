// C++ includes
#include <iostream>

// Project includes
#include "universalcommunicationmodule.hpp"

// print function limited to the scope of this class
void DEBUG(std::string x) {
    std::cout << x << std::endl;
}

UniversalCommunicationModule::UniversalCommunicationModule (){
    // TODO (TS): implement actual seral/cta init.
    DEBUG("\t...Open serial port");
    DEBUG("\t...Start CTA-2045 Module");
    DEBUG("\t...Query data link");
    DEBUG("\t...Query max payload");
    DEBUG("\t...Query message support");

    UniversalCommunicationModule::ProcessGetInformation ();
    UniversalCommunicationModule::ProcessGetTemperatureOffset ();
    UniversalCommunicationModule::ProcessGetSetPoint ();
    UniversalCommunicationModule::ProcessGetCommodityRead ();
    UniversalCommunicationModule::ProcessGetCommoditySubscription ();
}  // end constructor

UniversalCommunicationModule::~UniversalCommunicationModule (){

}  // end destructor

std::string UniversalCommunicationModule::Shed (int event_duration){
    // TODO (TS): implement CTA method call to return pass actual values and
    // wait for response.
    (void)event_duration;
    return "success";
}  // end Shed

std::string UniversalCommunicationModule::EndShed (){
    // TODO (TS): implement CTA method call to return pass actual values and
    // wait for response.
    return "success";
}  // end End Shed

std::string UniversalCommunicationModule::SetTemperatureOffset (
    int offset,
    char units) {
    // TODO (TS): implement CTA method call to return pass actual values and
    // wait for response.
    (void)offset;
    (void)units;
    return "success";
}  // end Shed

std::string UniversalCommunicationModule::SetCommodityRead (
    std::string commodity,
    double instantaneous_rate,
    double cumulative_amount) {
    // TODO (TS): implement CTA method call to return pass actual values and
    // wait for response.
    (void)commodity;
    (void)instantaneous_rate;
    (void)cumulative_amount;
    return "success";
}  // end Set Commodity Read

std::string UniversalCommunicationModule::SetCommoditySubscription(
    std::string commodity,
    unsigned int poll_rate) {
    // TODO (TS): implement CTA method call to return pass actual values and
    // wait for response.
    (void)commodity;
    (void)poll_rate;
    return "success";
}  // end Set Commodity Subscription

std::map<std::string, std::string>
UniversalCommunicationModule::GetInfo (){
    return information_;
}  // end Get Info

std::map<std::string, std::string>
UniversalCommunicationModule::GetTemperatureOffset (){
    return temperature_offset_;
}  // end Get Temperature Offset

std::map<std::string, std::string>
UniversalCommunicationModule::GetSetPoint (){
    return set_point_;
}  // end Get Set Point

std::map<std::string, std::string>
UniversalCommunicationModule::GetCommodityRead (){
    return commodity_;
}  // end Get Commodity Read

std::map<std::string, std::string>
UniversalCommunicationModule::GetCommoditySubscription (){
    return subscription_;
}  // end Get Commodity Subscription

void UniversalCommunicationModule::ProcessShed (){

}  // end Process Shed

void UniversalCommunicationModule::ProcessEndShed (){

}  // end Process End Shed

void UniversalCommunicationModule::ProcessGetInformation (){
    information_["Response Code"] = "success";
    information_["CEA-2045 Version"] = "0";
    information_["Vendor ID"] = "1234";
    information_["Device Type"] = "water heater - electric";
    information_["Device Revision"] = "0001";
    information_["Capability Bitmap"] = "temperature offset";
} // end Process Get Information

void UniversalCommunicationModule::ProcessGetTemperatureOffset (){
    temperature_offset_["Response Code"] = "success";
    temperature_offset_["Current Offset"] = "10";
    temperature_offset_["Units"] = "degrees F";
}  // end Process Get Temperature Offset

void UniversalCommunicationModule::ProcessSetTemperatureOffset (){

}  // end Process Set Temperature Offset

void UniversalCommunicationModule::ProcessGetSetPoint (){
    set_point_["Response Code"] = "success";
    set_point_["Device Type"] = "water heater - electric";
    set_point_["Units"] = "degrees F";
    set_point_["Set Point 1"] = "130";
}  // end Process Get Set Point

void UniversalCommunicationModule::ProcessSetSetPoint (){

}  // end Process Set Set Point

void UniversalCommunicationModule::ProcessGetCommodityRead (){
    commodity_["Response Code"] = "success";
    commodity_["Commodity Code"] = "Electricity Consumed";
    commodity_["Instantaneous Rate"] = "3000";
    commodity_["Cumulative Amount"] = "40000";
}  // end Process Get Commodity Read

void UniversalCommunicationModule::ProcessSetCommodityRead (){

}  // end Process Set Commodity Read

void UniversalCommunicationModule::ProcessGetCommoditySubscription (){
    subscription_["Response Code"] = "success";
    subscription_["Commodity Type"] = "Electricity Consumed";
    subscription_["Commodity Update Frequency"] = "1";
}  // end Process Get Commodity Subscription

void UniversalCommunicationModule::ProcessSetCommoditySubscription (){

}  // end Process Set Commodity Subscription
