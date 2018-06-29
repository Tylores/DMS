#include <wiringPi.h>
#include "include/GPIO.hpp"
#include "include/ts_utility.hpp"

// Constructor
GPIO::GPIO (const tsu::config_map& init_map) {
    wiringPiSetupGpio ();   // this sets wiringPi to use Broadcom's pin  numbers
} // end Constructor

// Destructor
GPIO::~GPIO () {

} // end Destructor

// SetupPinModes
// - INPUT, OUTPUT.
// - PWM_OUTPUT supported for pin 18
// - GPIO_CLOCK supported for pin 4
void GPIO::SetupPinModes () {
    // TODO (TS): create loop for each pin that is defined in init_map
    pinMode(pin, mode);
} //  end SetupPinModes

// SetupPinResistors
// - Sets the built-in pull up/down resistor for each GPIO pin
// - PUD_OFF, PUD_DOWN, PUD_UP
void GPIO::SetupPinResistors () {
    // TODO (TS): create loop for each pin that is defined in init_map
    pullUpDnControl (pin, pud);
} // end SetupPinResistors

// DigitalWrite
// - set an OUTPUT pin to HIGH = 1 or LOW = 0
void GPIO::DigitalWrite (int pin, int value) {
    digitalWrite (pin, value);
} // end DigitalWrite

// DigitalRead
// - reads an INPUT pin for HIGH = 1 or LOW = 0
int GPIO::DigitalRead (int pin) {
    return digitalRead (pin);
} // end DigitalRead

// AnalogWrite
// - writes a value 0 - 255, where 255 = supply voltage
void GPIO::AnalogWrite (int pin, float voltage) {
    int value = analog_range_ * voltage/supply_voltage_;
    analogWrite (pin, value);
} // end AnalogWrite

// AnalogRead
// - reads a value 0 - 255, where 255 = supply voltage
float GPIO::AlalogRead (int pin) {
    float percent = analogRead (pin) / analog_range_;
    return percent * supply_voltage_
} // end AlalogRead
