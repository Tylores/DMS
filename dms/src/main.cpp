/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Copyright (c) V2 Systems, LLC.  All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
******************************************************************************/

// INCLUDE
#include <iostream>     // cout, cin
#include <cstdio>       // printf
#include <thread>       // thread, join
#include <chrono>       // now, duration

#include "include/ts_utility.hpp"
#include "include/aj_utility.hpp"
#include "include/ServerListener.hpp"
#include "include/SmartGridDevice.hpp"
#include "include/ElectricVehicle.hpp"

using namespace std;
using namespace ajn;

bool done = false;  //signals program to stop

// Help
// - CLI interface description
static void Help () {
    printf ("\t[Help Menu]\t\n\n");
    printf ("> q \t\t\t quit\n");
    printf ("> h \t\t\t display help menu\n");
    printf ("> d \t\t\t display current properties\n");
    printf ("> u \t\t\t send current properties and get time/price\n");
    printf ("> o \t\t\t optimize charge schedule\n");
    printf ("> c \t\t\t charge when available\n");
    printf ("> k \t\t\t drive till dead\n");
} // end Help

// TerminalHelp
// - command line interface arguments during run, [] items have default values
static void CommandLineHelp (string& kArg) {
    const char* s = kArg.c_str();
    printf("\n[Usage] > %s -c file [-d file] [-m int] [-p file] [-h]\n", s);
    printf("\t -h \t help\n");
    printf("\t -c \t required configuration filename\n");
    printf("\t -d \t driver. (commuter, retired)\n");
    printf("\t -m \t model (Tesla, BMW, Leaf))\n");
    printf("\t -t \t time multiplier. (default = 300 i.e, 5 minutes)\n");
} // end TerminalHelp

// CommandLineParse
// - method to parse program initial parameters
static map<string, string> CommandLineParse (int argc, char** argv) {
    // parapeter tokens
    enum {HELP, CONFIG, DRIVER, MODEL, TIME};
    vector<string> tokens = {"-h", "-c", "-d", "-m", "-t"};
    string name = argv[0];

    // parse tokens
    map<string, string> parameters;
    string token, parameter;
    for (int i = 1; i < argc; i = i+2){
        token = argv[i];

        if (token.compare(tokens[HELP]) == 0) {
            CommandLineHelp(name);
            exit(EXIT_FAILURE);
        } else if (token.compare(tokens[CONFIG]) == 0) {
            parameter = argv[i+1];
            parameters["config"] = parameter;
        } else if (token.compare(tokens[DRIVER]) == 0) {
            parameter = argv[i+1];
            parameters["driver"] = parameter;
        } else if (token.compare(tokens[MODEL]) == 0) {
            parameter = argv[i+1];
            parameters["model"] = parameter;
        } else if (token.compare(tokens[TIME]) == 0) {
            parameter = argv[i+1];
            parameters["time"] = parameter;
        } else {
            const char* s = token.c_str();
            printf("[ERROR] : Invalid argument: %s\n", s);
            CommandLineHelp(name);
            exit(EXIT_FAILURE);
        }
    }
    return parameters;
} // end CommandLineParse

// CommandLineInterface
// - method to allow user controls durinng program run-time
static bool CommandLineInterface (string& input) {
    // check for program argument
    if (input == "") {
        return true;
    }
    char cmd = input[0];

    // deliminate input string to argument parameters
    vector<string> tokens;
    tokens = tsu::SplitString(input, ' ');
    if (tokens.empty()) {
        return true;
    }

    switch (cmd) {
    case 'q':
       return false;

    case 'h':
    default:
        Help();
        break;
    }

    return true;
}

void MainLoop () {
    Help ();
    string input;

    while (!done) {
        getline(cin, input);
        done = !CommandLineInterface(input);
    }
} // end MainLoop

// Main
// ----
int main (int argc, char** argv) {
    printf("\nStarting Program...\n");

    printf("\n\tLoading parameters...\n");
    if (argc == 1) {
        string name = argv[0];
        CommandLineHelp(name);
        return EXIT_FAILURE;
    }

    map<string, string> parameters = CommandLineParse(argc, argv);

    printf("\n\tMapping configuration file...\n");
    string config_file = parameters.at("config");
    tsu::config_map ini_map = tsu::MapConfigFile(config_file);

    printf("\n\tStarting AllJoyn...\n");
    assert(AllJoynInit() == ER_OK);
    #ifdef ROUTER
        assert(AllJoynRouterInit() == ER_OK);
    #endif // ROUTER

    printf("\n\t\tCreating message bus...\n");
    string app_name = tsu::GetSectionProperty(ini_map, "AllJoyn", "app");
    bool allow_remote = true;
    BusAttachment* bus_ptr = new BusAttachment(app_name.c_str(), allow_remote);
    assert(bus_ptr != NULL);

    printf("\n\t\tCreating about object...\n");
    AboutData about_data("en");
    AboutObj* about_ptr = new AboutObj(*bus_ptr);
    assert(about_ptr != NULL);

    #ifdef SECURE
        QCC_SetDebugLevel("ALLJOYN_AUTH", 3);
        QCC_SetDebugLevel("CRYPTO", 3);
        QCC_SetDebugLevel("AUTH_KEY_EXCHANGER", 3);
    #endif // SECURE

    printf("\n\t\tEstablishing session port...\n");
    aj_utility::SessionPortListener SPL;
    string port_number = tsu::GetSectionProperty(ini_map, "AllJoyn", "port");
    SessionPort port = stoul(port_number);

    printf("\n\t\tSetting up bus attachment...\n");
    QStatus status = aj_utility::SetupBusAttachment (
        ini_map, port, SPL, bus_ptr, &about_data
    );

    if (status != ER_OK) {
        delete about_ptr;
        delete bus_ptr;
        return EXIT_FAILURE;
    }

    printf("\n\t\tCreating observer...\n");
    string server_interface = tsu::GetSectionProperty(ini_map,
                                                      "AllJoyn",
                                                      "server_interface");
    const char* server_name = server_interface.c_str();
    Observer* obs_ptr = new Observer(*bus_ptr, &server_name, 1);

    printf("\n\t\tCreating listener...\n");
    ServerListener* listner_ptr = new ServerListener(bus_ptr,
                                                     obs_ptr,
                                                     server_name);
    obs_ptr->RegisterListener(*listner_ptr);

    printf("\n\t\tCreating bus object...\n");
    string device_interface = tsu::GetSectionProperty(ini_map,
                                                      "AllJoyn",
                                                      "device_interface");
    const char* device_name = device_interface.c_str();

    string path_str = tsu::GetSectionProperty(ini_map, "AllJoyn", "path");
    const char* path = path_str.c_str();

    SmartGridDevice* sgd_ptr = new SmartGridDevice(bus_ptr, device_name, path);

    printf("\n\t\t\tRegistering bus object...\n");
    if (ER_OK != bus_ptr->RegisterBusObject(*sgd_ptr)){
        printf("\n\t\t\t[ERROR] failed registration...\n");
        delete &sgd_ptr;
        return EXIT_FAILURE;
    }
    about_ptr->Announce(port, about_data);

    printf("\n\t\tLooking for electric vehicle...\n");
    string driver = parameters.at("driver");
    string model = parameters.at("model");
    unsigned int time_mult = stoul(parameters.at("time"))/60;
    ElectricVehicle EV (ini_map, driver, model, time_mult);

    printf("\n\tProgram initialization complete...\n\n");
    thread CLI(MainLoop);

    unsigned int time_new;
    int price_new, power, energy, state;
    while (!done) {

        // time the total ev control process
        auto time_start = chrono::high_resolution_clock::now();
        // EV control loop
        time_new = listner_ptr->time_;
        if (time_new != 0) {
            price_new = listner_ptr->price_;
            EV.Control(time_new, price_new);
            state = EV.state_;
            power = EV.power_now_;
            energy = EV.energy_request_;
            sgd_ptr->UpdatePowerStatus(time_new, state, power, energy);
        }

        auto time_end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> time_elapsed = time_end - time_start;

        int time_wait = 1000;  // milliseconds

        // determine sleep duration after deducting process time
        int time_remaining = (time_wait - time_elapsed.count());
        time_remaining = (time_remaining > 0) ? time_remaining : 0;
        this_thread::sleep_for (chrono::milliseconds (time_remaining));
    }

    printf("\nProgram shutting down...\n");
    printf("*****\n****\n***\n**\n*\n\n");
    delete sgd_ptr;
    delete listner_ptr;
    delete obs_ptr;
    delete about_ptr;
    delete bus_ptr;
    CLI.join();

    return EXIT_SUCCESS;
} // end main
