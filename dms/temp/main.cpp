#include <iostream>
#include "universalcommunicationmodule.hpp"
#include "waterheater.hpp"

using namespace std;

int main()
{
    WaterHeater WH;
    WH.Shed(60);
    WH.PrintProperties();
    return 0;
}
