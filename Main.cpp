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
	void Write(std::string command, char opcode2);
	std::string Read (std::string);

private:
	// member properties
	enum{
		MSB, LSB, PAYLOAD1, PAYLOAD2, OPCODE1, OPCODE2, MAXTIMEOUT = 20
	};
};

class WaterHeater
{
public:	
	int energyTake;		//per UML diagram.
	int temperature;
	
	void shed(char duration)
	{
		//const char* shed = "shed"; //Creates a pointer that I could pass to a program.
		//char* duration = dur	   //Creates a pointer for the duration.
		CTA2045 CTA;
		CTA.CTA2045::Write("shed", duration);
		//std::string update = CTA2045::Read(energyTake)
		
		//energyTake = map[energyTake];
		//temperature = map[temperature];
		
		//std::cout<<shed<<std::endl;
	}
	
		void endShed()
	{ 
		//const char* endShed = "endShed";
		char zero = 0x00;
		CTA2045 CTA;
		CTA.CTA2045::Write("end shed", zero);	
	}
	
	
	void loadUp(char duration)
	{
		CTA2045 CTA;	
		CTA.CTA2045::Write("load up", duration);	
	}
	
	// Per Conversation with Tylor, we are not including ACK and NAK.
	
	void requestForPowerLevel(char duration)
	{
		CTA2045 CTA;	
		CTA.CTA2045::Write("request for power level", duration);	
	}
	
	
	// Per Conversation with Tylor, we are not including Price related functions.
	
	void criticalPeakEvent(char duration)
	{
		CTA2045 CTA;
		CTA.CTA2045::Write("critical peak event", duration);	
	}
	
	void gridEmergency(char duration)
	{
		CTA2045 CTA;
		CTA.CTA2045::Write("grid emergency", duration);	
	}
	
	void gridGuidance(char duration)
	{
		CTA2045 CTA;
		CTA.CTA2045::Write("grid guidance", duration);	
	}
	
		// Per Conversation with Tylor, we are not including Outside Communication Connection Status.

	void customerOverride(bool status) // on = 1, off = 0.
	{
		CTA2045 CTA;
		CTA.CTA2045::Write("customer override", status);	
	}
	
	void queryWhatIsYourOperationalState() 
	{
		char zero = 0x00;
		CTA2045 CTA;
		CTA.CTA2045::Write("query: what is your operational state", zero);	
	}
	
	void stateResponseQuery(char status) // on = 1, off = 0.
	{
		CTA2045 CTA;
		CTA.CTA2045::Write("state query response", status);	
	}
	
	void sleep()
	{
		char zero = 0x00;
		CTA2045 CTA;
		CTA.CTA2045::Write("sleep", zero);	
	}
	
	void wakeRefreshRequest()
	{
		char zero = 0x00;
		CTA2045 CTA;
		CTA.CTA2045::Write("wake / refresh request", zero);	
	}
	
};
	
int main()
{
	
	
	WaterHeater WH;
	WH.energyTake = 0x12;
	WH.temperature = 0x02;
	char test = WH.energyTake + WH.temperature;
			std::cout << (int)test << std::endl;

//	char a;
		//int a = sizeof(byte);
		std::cout << "HELLO WORLD!" << std::endl;
		//std::cout << a << std::endl;

		std::cin.get();
		return 0;
}
