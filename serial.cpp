#include <wiringSerial.h>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <bitset>

int main (void) {
  // convert hex to string
  // - I need to define how the hex values will be input and spaced so I can create
  // - my converter function.
  std::string hex = "48";
  std::string hex_str = "";
  for (size_t i = 0; i < hex.length(); i+=2) {
    std::string byte = hex.substr(i,2);
    char c = (char) (int)strtol(byte.c_str(), NULL, 16);
    hex_str.push_back(c);
  }
  std::cout << "The hex value is: " << hex_str << std::endl;

  std::chrono::milliseconds period(1000);

  std::string name = "/dev/ttyUSB0";
  int baud = 19200;
  int file_descriptor = serialOpen(name.c_str(), baud);
  std::cout << "device descriptor: " << file_descriptor  << std::endl;
  int data;
  for (;;)
  {
    data = serialDataAvail (file_descriptor);
    std::cout << "data available: " << data << std::endl;

    std::cout << "The hex value is: " << hex_str.c_str() << std::endl;
    serialPuts(file_descriptor, hex_str.c_str());

    std::this_thread::sleep_for(period);
  }
  serialClose(file_descriptor);
  return 0 ;
}
