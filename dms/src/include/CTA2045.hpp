#ifndef CTA2045_H
#define CTA2045_H


class CTA2045 {
public :
    // member functions
    CTA2045(const tsu::config_map& init_map);
    virtual ~CTA2045();
    std::string Write (std::string command, T argument = NULL);
    std::map <std::string, std::string> Read (std::string command);

private:
    // member properties
    enum {
        MSB, LSB, PAYLOAD1, PAYLOAD2, OPCODE1, OPCODE2, MAXTIMEOUT = 20
    }
private :
    // local functions for control
    void Checksum ();
    void Heartbeat ();
    void Payload ();
};

#endif // CTA2045_H
