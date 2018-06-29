#include "CTA2045.hpp"

// Constructor
CTA2045::CTA2045 () {

} // end Constructor

// Destructor
CTA2045::~CTA2045 () {

} // end Destructor

// Write
// - convert string to opcode 1 and optional argument to opcode 2
// - send serial signal to connected module and wait for response.
// - return error code
template <typename T>
std::string CTA2045::Write(std::string command, T argument) {

} // end Write

// Read
// - convert string to opcode 1 and optional argument to opcode 2
// - send serial signal to connected module and wait for response.
// - convert response to map for user to parse.
std::map <std::string, std::string> CTA2045::Read (std::string command) {

} // end Read

// Checksum
// - validate message
void CTA2045::Checksum () {

} // end Checksum

// Heartbeat
// - informs the connected module that it is still being controlled
void CTA2045::Heartbeat () {

} // end Heartbeat

// Payload
// - the message format for CTA2045 communications
void CTA2045::Payload () {

} // end Payload
