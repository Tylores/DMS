#ifndef CTA2045_H
#define CTA2045_H


class CTA2045 {
public :
    // member functions
    CTA2045(const tsu::config_map& init_map);
    virtual ~CTA2045();
    void Checksum ();
    void Heartbeat ();
    void Payload ();
    void Write (std::string command, );
    std::string Read (std::string );

private:
    // member properties
    enum {
        MSB, LSB, PAYLOAD1, PAYLOAD2, OPCODE1, OPCODE2, MAXTIMEOUT = 20
    }

};

#endif // CTA2045_H
