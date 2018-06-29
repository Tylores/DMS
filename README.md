# custEV: Smart Energy Controller for Customer EV

* Portland State University, Department of Electrical Engineering
* V2 Systems, LLC Portland Oregon

A Smart Energy controller agent for an Electric Vehicle (Smart Grid Device or SGD). 

Commands for the SGD can be entered by the user via a command line interface (console), or commands can be received from the AllJoyn Interface.  The program contains a simple model of an Electric Vehicle Battery and can be programmed to emulate arbitrary driving patterns. The AllJoyn interface can be configured to use encryption.

## Project setup

Install the AllJoyn Framework: Information regarding AllJoyn can be found at https://wiki.alljoyn.org. 

The file tools/appsetup contains the environment variables needed for compiling and running the agents.  Copy this file over to your $HOME/bin directory (or any other directory that is in the default PATH). Change to environment variable $AJ_ROOT to point to where you have installed AllJoyn. 
 
To set up proper environment variables for compiling program:
>   source appsetup

Change to the source code directory:
>    cd custEV

Compile the program:
>    make

Note: to enable the secure interface example set SECURE to '1' using the cpp option "-DSECURE" in the makefile

## Customer EV Agent Usage

cd custEV

The  unit is invoked from the command line as follows:
>    ./bin/Debug/custEV -c config-file  

An example config file is "../data/custEV.ini".

For help on other command line arguments enter:
>    ./bin/Debug/custEV -h 

Once the program is running, enter 'h' for help on command line options

The configuration files defines the names of the following files:  
* output log file name

## EV Agent

The CustEV agent is comprised of two main modules, the Smart Grid Device Controller (*sgdControl*), and a model of the EV Battery (*evBatteryModel*).  

The *sgdControl* is a conceptual model of the EV charger; it knows when the vehicle is plugged-in and sends and receives information from the EV battery.

The *evBatteryModel* models the charging and discharging of the EV Battery.  

## AllJoyn Interfaces
```
# types: ‘q’=uint16_t, 'n'=int16_t, 's'=string, 'i'=int32_t, 'u'=uint32_t, 'v'=various
<node>
    <interface name="edu.pdx.powerlab.sep.edev">
      <description language="en">
	Demonstration interface emulating function sets of SEP end device
      </description>

      <property name="AssetName" type="s" access="read">
         <description language = "en">
             Assigned asset name
         </description>
         <annotation name="org.freedesktop.DBus.Property.EmitsChangedSignal" value=”False”/>
      </property>

      <property name="PowerStatus" type="a{sv}" access="read">
         <description language= "en">
           String/value pairs representing the PowerStatus resource
           batteryStatus:Uint8 (where 0 = unknown, 4 = not applicable (mains powered only)
           changedTime:uint32_2 (SEP definition: TimeType)
           chargingPowerNow:int32_t (SEP definition: ActivePower)
           energyRequetNow:int32_t (SEP definition: RealEnergy)
         </description>
         <annotation name="org.freedesktop.DBus.Property.EmitsChangedSignal" value=”True”/>
      </property>
    </interface>


    <interface name="edu.pdx.powerlab.sep.server">
      <description language="en">
	Demonstration interface emulating function sets of SEP server
      </description>

      <property name="EMSName" type="s" access="read">
         <description language = "en">
             Assigned EMS name
         </description>
         <annotation name="org.freedesktop.DBus.Property.EmitsChangedSignal" value=”False”/>
      </property>

      <property name="Time" type="u" access="read">
         <description language= "en">
           TimeType: A 64 bit value holding the number of seconds sincd 00:00 Jan 1,1970,UTC.
         </description>
         <annotation name="org.freedesktop.DBus.Property.EmitsChangedSignal" value=”True”/>
      </property>

      <property name="price" type="i" access="read">
         <description language= "en">
           Assumes that the starting time of the price is "now" and set until a new price is distributed
           The price value is an integer, representing 1/10 of a cent per kWh.  For example,
           25 to represents 2.5 cents.
         </description>
         <annotation name="org.freedesktop.DBus.Property.EmitsChangedSignal" value=”True”/>
      </property>
     </interface>              
</node>
```

CustEMS agent is a consumer of end device properties and producer of server properties.  The EMS caches the asset properties.

CustEV agentis a producer of end device properties and consumer of server properties. The EV does not cache EMS properties.




