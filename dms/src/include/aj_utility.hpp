/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *    Copyright (c) V2 Systems, LLC.  All rights reserved.
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
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
**********************************************************/

#ifndef AJ_UTILITY_HPP_INCLUDED
#define AJ_UTILITY_HPP_INCLUDED

#include <alljoyn/Status.h>
#include <alljoyn/AboutObj.h>
#include <alljoyn/BusAttachment.h>
#include <alljoyn/Observer.h>
#include <alljoyn/Init.h>

#ifdef SECURE
    #include <alljoyn/AuthListener.h>
    #include <alljoyn/Log.h>
#endif // SECURE

#include "ts_utility.hpp"

namespace aj_utility {

// SPL
// - accept or reject incoming join requests
class SessionPortListener : public ajn::SessionPortListener {
    virtual bool AcceptSessionJoiner (ajn::SessionPort sessionPort,
                                      const char* joiner,
                                      const ajn::SessionOpts& opts) {

        std::cout<< "\tJoin session request: " << joiner << std::endl;
        return true;
    }
}; // end SessionPortListener

// BuildDeviceInterface
// - method to build alljoyn interface for local device
static QStatus BuildDeviceInterface (std::string name,
                                     ajn::BusAttachment* bus_ptr) {
    QStatus status;
    const char* interface_name = name.c_str();
    ajn::BusAttachment& bus_ref = *bus_ptr;  // deref pointer
    ajn::InterfaceDescription* interface = NULL;

    printf("\n\t\t\t\tCreating blank interface for %s...\n",interface_name);
    #ifdef SECURE
        status = bus_ref.CreateInterface (interface_name, interface,true);
        assert (status == ER_OK);
    #else
        status = bus_ref.CreateInterface(interface_name, interface);
        assert (status == ER_OK);
    #endif // SECURE

    printf("\n\t\t\t\tAdding properties...\n");
    status = interface->AddProperty("AssetName", "s", ajn::PROP_ACCESS_READ);
    assert (status == ER_OK);

    status = interface->AddPropertyAnnotation(
        "AssetName",
        "org.freedesktop.DBus.Property.EmitsChangedSignal",
        "const"
    );
    assert (status == ER_OK);

    status = interface->AddProperty("PowerStatus",
                                    "a{sv}",
                                    ajn::PROP_ACCESS_READ);
    assert (status == ER_OK);

    status = interface->AddPropertyAnnotation(
        "PowerStatus",
        "org.freedesktop.DBus.Property.EmitsChangedSignal",
        "true"
    );
    assert (status == ER_OK);

    printf("\n\t\t\t\tActivating interface...\n");
    interface->Activate();

    return status;
} // end BuildDeviceInterface

// BuildServerInterface
// - method to create alljoyn interface for remote device
static QStatus BuildServerInterface (std::string name,
                                     ajn::BusAttachment* bus_ptr) {
    QStatus status;
    const char* interface_name = name.c_str();
    ajn::BusAttachment& bus_ref = *bus_ptr;  // deref pointer
    ajn::InterfaceDescription* interface = NULL;

    printf("\n\t\t\t\tCreating blank interface for %s...\n",interface_name);
    #ifdef SECURE
        status = bus_ref.CreateInterface (interface_name, interface, true);
        assert (status = ER_OK);
    #else
        status = bus_ref.CreateInterface(interface_name, interface);
        assert (status == ER_OK);
    #endif // SECURE

    printf("\n\t\t\t\tAdding properties...\n");
    status = interface->AddProperty("EMSName", "s", ajn::PROP_ACCESS_READ);
    assert (status == ER_OK);

    status = interface->AddPropertyAnnotation(
        "EMSName",
        "org.freedesktop.DBus.Property.EmitsChangedSignal",
        "const"
    );
    assert (status == ER_OK);

    status = interface->AddProperty("Time", "u", ajn::PROP_ACCESS_READ);
    assert (status == ER_OK);

    status = interface->AddPropertyAnnotation(
        "Time",
        "org.freedesktop.DBus.Property.EmitsChangedSignal",
        "true"
    );
    assert (status == ER_OK);

    status = interface->AddProperty("price", "i", ajn::PROP_ACCESS_READ);
    assert (status == ER_OK);

    status = interface->AddPropertyAnnotation(
        "price",
        "org.freedesktop.DBus.Property.EmitsChangedSignal",
        "true"
    );
    assert (status == ER_OK);

    printf("\n\t\t\t\tActivating interface...\n");
    interface->Activate();

    return status;
} // end BuildServerInterface

// SetupBusAttachment
// - start/connect to alljoyn message bus and build the server/device interfaces
static QStatus SetupBusAttachment (const tsu::config_map& ini_map,
                                   ajn::SessionPort& port,
                                   ajn::SessionPortListener& SPL,
                                   ajn::BusAttachment* bus_ptr,
                                   ajn::AboutData* about_ptr) {
    QStatus status;
    ajn::BusAttachment& bus_ref = *bus_ptr;  // deref pointer
    ajn::AboutData& about_ref = *about_ptr;  // deref pointer

    printf("\n\t\t\tStarting bus...\n");
    status = bus_ref.Start();
    assert (status == ER_OK);

    printf("\n\t\t\tConnecting to bus...\n");
    status = bus_ref.Connect();
    if (status != ER_OK) {
        return status;
    }

    printf("\n\t\t\tBuilding server interface...\n");
    std::string server_interface = tsu::GetSectionProperty (ini_map,
                                                       "AllJoyn",
                                                       "server_interface");
    status = aj_utility::BuildServerInterface (server_interface, &bus_ref);
    assert (status == ER_OK);

    printf("\n\t\t\tBuilding device interface...\n");
    std::string device_interface = tsu::GetSectionProperty (ini_map,
                                                       "AllJoyn",
                                                       "device_interface");
    status = aj_utility::BuildDeviceInterface (device_interface, &bus_ref);
    assert (status == ER_OK);

    ajn::SessionOpts opts(ajn::SessionOpts::TRAFFIC_MESSAGES,
                          false,
                          ajn::SessionOpts::PROXIMITY_ANY,
                          ajn::TRANSPORT_ANY);

    printf("\n\t\t\tBinding to session port...\n");
    bus_ref.BindSessionPort(port, opts, SPL);

    printf("\n\t\t\tSetting about data...\n");
    uint8_t appID[] = { 0x47, 0xFD, 0xB0, 0x08,
                        0x25, 0x22, 0x48, 0x98,
                        0x9B, 0xAE, 0xE2, 0xE2,
                        0x05, 0xBD, 0x79, 0xEE };
    about_ref.SetAppId(appID, 16);
    about_ref.SetDeviceName("Customer Electric Vehicle Smart Energy Agent");
    about_ref.SetDeviceId("7a439b61-3128-49f9-8a8b-65471a8fdeeb");
    about_ref.SetAppName("PSU Smart Energy");
    about_ref.SetManufacturer("PSU");
    about_ref.SetModelNumber("00001");
    about_ref.SetDescription("Grid Friendly Energy Management Application");
    about_ref.SetDateOfManufacture("2016-06-06");
    about_ref.SetSoftwareVersion("0.0.1");
    about_ref.SetHardwareVersion("0.0.1");
    about_ref.SetSupportUrl("http://www.example.org");

    if (!about_ref.IsValid()) {
        std::cerr << "[ERROR] Invalid About data. " << std::endl;
        return ER_FAIL;
    }

    #ifdef SECURE
        status = bus_ref.EnablePeerSecurity(
            ECDHE_KEYX,
            new ECDHEKeyXListener(),
            ".alljoyn_keystore/custEV_ecdhe.ks",
            false
        );
        assert (status == ER_OK);
    #endif //SECURE
    return status;
} // end SetupBusAttachment

} // end aj_utility

#endif // AJ_UTILITY_HPP_INCLUDED
