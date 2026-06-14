/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "AptBackend.h"

#include <sdbus-c++/sdbus-c++.h>

#include <iostream>

namespace Packages {
bool AptBackend::update() {
  try {
    auto connection = sdbus::createSystemBusConnection();
    auto systemd = sdbus::createProxy(
      *connection,
      sdbus::ServiceName{"org.freedesktop.systemd1"},
      sdbus::ObjectPath{"/org/freedesktop/systemd1"});

    std::cout << "Updating...\n";

    systemd->callMethod("StartUpdate")
    .onInterface("org.maintenanced.Updater1")
    .withArguments("maintenance-apt.service", "replace");

    auto proxy = sdbus::createProxy(
      *connection,
      sdbus::ServiceName{"org.maintenanced.Updater1"},
      sdbus::ObjectPath{"/org/maintenanced/Updater1"});

    proxy->uponSignal("Started")
    .onInterface("org.maintenanced.Updater1")
    .call([]() {
      std::cout << "Started\n";
    });

    proxy->uponSignal("Finished")
    .onInterface("org.maintenanced.Updater1")
    .call([]() {
      std::cout << "Finished\n";
    });

    connection->enterEventLoop();
  } catch (const sdbus::Error& e) {
    std::cerr << "Failed to connect to updater: " << e.what() << "\n";
    return false;
  }
  return true;
}
std::string AptBackend::name() const { return "apt"; }
}  // namespace Packages
