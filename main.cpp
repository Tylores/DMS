

#include <iostream>
#include <string>
#include <map>

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
  void IntWrite(std::string command, char opcode1, char opcode2)
  std::string Read (std::string);

private:
  // member properties
  enum{
    MSB, LSB, PAYLOAD1, PAYLOAD2, OPCODE1, OPCODE2, MAXTIMEOUT = 20
  };
};

class WaterHeater : public CTA2045
{
public:
  int energy_take_;		//per UML diagram.
  int temperature_;

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
    Write("end shed", zero);
  }


  void LoadUp(char duration)
  {
    //CTA2045 CTA;
    Write("load up", duration);
  }

  // Per Conversation with Tylor, we are not including ACK and NAK.

  void RequestForPowerLevel(char percent)
  {
    //CTA2045 CTA;
    Write("request for power level", percent);
  }


  // Per Conversation with Tylor, we are not including Price related functions.

  void CriticalPeakEvent(char duration)
  {
    //CTA2045 CTA;
    Write("critical peak event", duration);
  }

  void GridEmergency(char duration)
  {
    //CTA2045 CTA;
    Write("grid emergency", duration);
  }

  void GridGuidance(char duration)
  {
    //CTA2045 CTA;
    Write("grid guidance", duration);
  }

  // Per Conversation with Tylor, we are not including Outside Communication Connection Status.

  void CustomerOverride(bool status) // on = 1, off = 0.
  {
    //CTA2045 CTA;
    Write("customer override", status);
  }

  void QueryWhatIsYourOperationalState()
  {
    char zero = 0x00;
    //CTA2045 CTA;
    Write("query: what is your operational state", zero);
  }

  void StateResponseQuery(char status) // on = 1, off = 0.
  {
    //CTA2045 CTA;
    Write("state query response", status);
  }

  void Sleep()
  {
    char zero = 0x00;
    //CTA2045 CTA;
    Write("sleep", zero);
  }

  void WakeRefreshRequest()
  {
    char zero = 0x00;
    //CTA2045 CTA;
    Write("wake / refresh request", zero);
  }

};


  void InfoRequest()
  {
    char zero = 0x00;
    //CTA2045 CTA;
    Write("wake / refresh request", zero);
  }

};


//using namespace std;

int main()
{


  WaterHeater WH;
  WH.energy_take_ = 0x12;
  WH.temperature_ = 0x02;
  char test = WH.energy_take_ + WH.temperature_;
      std::cout << (int)test << std::endl;

//	char a;
    //int a = sizeof(byte);
    std::cout << "HELLO WORLD!" << std::endl;
    //std::cout << a << std::endl;

    std::cin.get();
    return 0;
}

