#ifndef UNIVERSALCOMMUNICATIONMODULE_H
#define UNIVERSALCOMMUNICATIONMODULE_H

#include <string>
#include <map>

class UniversalCommunicationModule
{
public:
    UniversalCommunicationModule();
    virtual ~UniversalCommunicationModule();
    std::string Shed (int event_duration);
    std::string EndShed ();
    std::string SetTemperatureOffset (int offset, char units);
    std::string SetSetPoint (std::string device_type,
                             char units,
                             unsigned int set_high);
    std::string SetCommodityRead (std::string commodity,
                                  double instantaneous_rate,
                                  double cumulative_amount);
    std::string SetCommoditySubscription (std::string commodity,
                                          unsigned int poll_rate);
    std::map<std::string, std::string> GetInfo ();
    std::map<std::string, std::string> GetTemperatureOffset ();
    std::map<std::string, std::string> GetSetPoint ();
    std::map<std::string, std::string> GetCommodityRead ();
    std::map<std::string, std::string> GetCommoditySubscription ();

private :
    // member maps
    std::map<std::string, std::string> information_;
    std::map<std::string, std::string> temperature_offset_;
    std::map<std::string, std::string> set_point_;
    std::map<std::string, std::string> commodity_;
    std::map<std::string, std::string> subscription_;

private :
    // Basic
    void ProcessShed ();
    void ProcessEndShed ();

    // Intermediate
    void ProcessGetInformation ();
    void ProcessGetTemperatureOffset ();
    void ProcessSetTemperatureOffset ();
    void ProcessGetSetPoint ();
    void ProcessSetSetPoint ();
    void ProcessGetCommodityRead ();
    void ProcessSetCommodityRead ();
    void ProcessGetCommoditySubscription ();
    void ProcessSetCommoditySubscription ();
};

#endif // UNIVERSALCOMMUNICATIONMODULE_H
