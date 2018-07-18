

#include <iostream>
#include <string>
#include <map>
#include <sstream>

class CTA2045
{
public:

  // member functions
  //CTA2045(const tsu::config_map& init_map);
  virtual ~CTA2045();
  void Checksum();
  void Heartbeat();
  void Payload();
  void Write(std::string command, char opcode1);
  void IntWrite(std::string command, char opcode1, char opcode2);
  std::string Read (std::string);
  std::string InfoRequest(std::string info); //This should return a map, but not sure how to do it.
  //void infoRequest();

private:
  // member properties
  enum{
    MSB, LSB, PAYLOAD1, PAYLOAD2, OPCODE1, OPCODE2, MAXTIMEOUT = 20
  };
};

class WaterHeater //: public CTA2045
{
public:
  int energy_take_;		//per UML diagram.
  int temperature_;
  CTA2045 CTA;
private:
  void Shed(char duration)
  {
    //const char* shed = "shed"; //Creates a pointer that I could pass to a program.
    //char* duration = dur	   //Creates a pointer for the duration.
    //CTA2045 CTA;
    CTA.CTA2045::Write("shed", duration);
    //std::string update = CTA2045::Read(energyTake)

    //energyTake = map[energyTake];
    //temperature = map[temperature];

    //std::cout<<shed<<std::endl;
  }

  void EndShed()
  {
    //const char* endShed = "endShed";
    char zero = 0x00;
    //CTA2045 CTA;
    CTA.CTA2045::Write("end shed", zero);
  }


  void LoadUp(char duration)
  {
    //CTA2045 CTA;
    CTA.CTA2045::Write("load up", duration);
  }

  // Per Conversation with Tylor, we are not including ACK and NAK.

  void RequestForPowerLevel(char percent)
  {
    //CTA2045 CTA;
    CTA.CTA2045::Write("request for power level", percent);

  }


  // Per Conversation with Tylor, we are not including Price related functions.

  void CriticalPeakEvent(char duration)
  {
    //CTA2045 CTA;
    CTA.CTA2045::Write("critical peak event", duration);
  }

  void GridEmergency(char duration)
  {
    //CTA2045 CTA;
    CTA.CTA2045::Write("grid emergency", duration);
  }

  void GridGuidance(char duration)
  {
    //CTA2045 CTA;
    CTA.CTA2045::Write("grid guidance", duration);
  }

  // Per Conversation with Tylor, we are not including Outside Communication Connection Status.

  void CustomerOverride(bool status) // on = 1, off = 0.
  {
    //CTA2045 CTA;
    CTA.CTA2045::Write("customer override", status);
  }

  void QueryWhatIsYourOperationalState()
  {
    char zero = 0x00;
    //CTA2045 CTA;
    CTA.CTA2045::Write("query: what is your operational state", zero);
  }

  void StateResponseQuery(char status) // on = 1, off = 0.
  {
    //CTA2045 CTA;
    CTA.CTA2045::Write("state query response", status);
  }

  void Sleep()
  {
    char zero = 0x00;
    //CTA2045 CTA;
    CTA.CTA2045::Write("sleep", zero);
  }

  void WakeRefreshRequest()
  {
    char zero = 0x00;
    //CTA2045 CTA;
    CTA.CTA2045::Write("wake / refresh request", zero);
  }

//};


  void InfoRequest()
  {
    //extern string infoRequest();

    char zero = 0x00;
    //CTA2045 CTA;
    CTA.CTA2045::Write("wake / refresh request", zero);
    /*
    unsigned int opcode1 = atoi(infoRequest.at(Opcode1));
    unsigned int opcode2 = atoi(infoRequest.at(Opcode2));
    unsigned int responseCode = atoi(infoRequest.at(ResponseCode));
    */
    unsigned int version = atoi(CTA.CTA2045::InfoRequest.at(std::string Version));
    unsigned int vendorID = atoi(CTA.CTA2045::InfoRequest.at(VendorID));
    unsigned int deviceType = atoi(CTA.CTA2045::InfoRequest.at(DeviceType));
    unsigned int deviceRevision = atoi(CTA.CTA2405::InfoRequest.at(DeviceRevision));

  }
};


//using namespace std;

int main()
{
  int AmbientTemp = 65;
  int SetPoint = 120; // This should be calculated based on status query.
  int TotalEnergy = 20000 // Joules. We should be able to look this up.

  WaterHeater WH;
  WH.energy_take_ = (WH.RequestForPowerLevel() * TotalEnergy) / 127;
  // This returns a 2-bit Hex, with 0x7F=100% and 0x00=0%.

  WH.temperature_ = AmbientTemp + ((SetPoint - AmbientTemp) * ((WH.RequestForPowerLevel()*100) / 127)) / 100;



  //char test = WH.energy_take_ + WH.temperature_;
  //    std::cout << (int)test << std::endl;

    std::cout << "HELLO WORLD!" << std::endl;
    std::cout << WH.energy_take_ << std::endl;
    std::cout << WH.temperature_ << std::endl;

    std::cin.get();
    return 0;
}

