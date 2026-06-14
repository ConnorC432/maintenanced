/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "PacmanBackend.h"

#include <sdbus-c++/sdbus-c++.h>

#include <condition_variable>
#include <iostream>
#include <map>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

static constexpr const char* SYSTEMD_BUS = "org.freedesktop.systemd1";
static constexpr const char* SYSTEMD_PATH = "/org/freedesktop/systemd1";
static constexpr const char* MANAGER_IFACE = "org.freedesktop.systemd1.Manager";
static constexpr const char* UNIT_IFACE = "org.freedesktop.systemd1.Unit";
static constexpr const char* PROPS_IFACE = "org.freedesktop.DBus.Properties";

namespace Packages {
bool PacmanBackend::update() {
  const std::string unitName = "maintenanced-pacman.service";
  auto connection = sdbus::createSystemBusConnection();
  connection->enterEventLoopAsync();

  auto systemd =
      sdbus::createProxy(*connection, sdbus::ServiceName{SYSTEMD_BUS},
                         sdbus::ObjectPath{SYSTEMD_PATH});

  systemd->callMethod("Subscribe").onInterface(MANAGER_IFACE);

  sdbus::ObjectPath unitPath;
  systemd->callMethod("LoadUnit")
      .onInterface(MANAGER_IFACE)
      .withArguments(unitName)
      .storeResultsTo(unitPath);

  auto unit = sdbus::createProxy(*connection, sdbus::ServiceName{SYSTEMD_BUS},
                                 sdbus::ObjectPath{unitPath});

  std::mutex m;
  std::condition_variable cv;
  std::optional<sdbus::ObjectPath> wantedJob;
  bool startJobFinished = false;
  bool serviceFinished = false;
  std::string startResult;
  std::string finalActiveState;

  systemd->registerSignalHandler(
      sdbus::InterfaceName(MANAGER_IFACE), sdbus::SignalName("JobRemoved"),
      [&](sdbus::Signal signal) {
        uint32_t jobId;
        sdbus::ObjectPath jobPath;
        std::string unit;
        std::string result;
        signal >> jobId >> jobPath >> unit >> result;

        std::lock_guard lk(m);
        if (wantedJob && jobPath == *wantedJob) {
          startJobFinished = true;
          startResult = result;
          std::cout << "Start job finished: " << startResult << std::endl;
          cv.notify_all();
        }
      });

  unit->registerSignalHandler(
      sdbus::InterfaceName(PROPS_IFACE), sdbus::SignalName("PropertiesChanged"),
      [&](sdbus::Signal signal) {
        std::string iface;
        std::map<std::string, sdbus::Variant> changed;
        std::vector<std::string> invalidated;
        signal >> iface >> changed >> invalidated;

        if (iface != UNIT_IFACE) return;

        auto it = changed.find("ActiveState");
        if (it == changed.end()) return;

        const auto state = it->second.get<std::string>();
        std::cout << "Active state: " << state << std::endl;

        if (state == "inactive" || state == "failed") {
          std::lock_guard lk(m);
          finalActiveState = state;
          serviceFinished = true;
          cv.notify_all();
        }
      });

  sdbus::ObjectPath jobPath;
  systemd->callMethod("StartUnit")
      .onInterface(MANAGER_IFACE)
      .withArguments(unitName, "replace")
      .storeResultsTo(jobPath);
  {
    std::unique_lock lk(m);
    wantedJob = jobPath;
  }

  {
    std::unique_lock lk(m);
    cv.wait(lk, [&] { return startJobFinished; });
  }

  if (startResult != "done") {
    std::cerr << "Service did not start successfully: " << startResult
              << std::endl;
    return false;
  }

  std::cout << "Service started successfully" << std::endl;

  {
    std::unique_lock lk(m);
    cv.wait(lk, [&] { return serviceFinished; });
  }

  std::cout << "Service finished with state: " << finalActiveState << std::endl;

  return true;
}

std::string PacmanBackend::name() const { return "pacman"; }

}  // namespace Packages
