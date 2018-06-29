#ifndef GPIO_H
#define GPIO_H

class GPIO {
public :
    // member functions
    GPIO (const tsu::config_map& init_map);
    virtual ~GPIO ();
    void SetPinModes ();
    void SetPinResistors ();
    void DigitalWrite (int pin, int value);
    int DigitalRead (int pin);
    void AnalogWrite (int pin, float voltage);
    float AnalogRead (int pin);

private :
    // member properties
    float supply_voltage_ = 3.3;    // volts
    int analog_range_ = 255;        // byte max
};

#endif // GPIO_H
