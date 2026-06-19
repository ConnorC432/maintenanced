/*
Created by Connor on 15/06/2026.
Copyright (c) 2026
All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "PackageManagerBackend.h"

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
PackageManagerBackend::PackageManagerBackend(std::string unitName,
                                             std::string backendName)
    : unitName_(std::move(unitName)), backendName_(std::move(backendName)) {}

std::string PackageManagerBackend::backendName() const { return backendName_; }

bool PackageManagerBackend::update() {
  auto connection = sdbus::createSystemBusConnection();
  connection->enterEventLoopAsync();

  auto systemd =
      sdbus::createProxy(*connection, sdbus::ServiceName{SYSTEMD_BUS},
                         sdbus::ObjectPath{SYSTEMD_PATH});

  systemd->callMethod("Subscribe").onInterface(MANAGER_IFACE);

  sdbus::ObjectPath unitPath;
  systemd->callMethod("LoadUnit")
      .onInterface(MANAGER_IFACE)
      .withArguments(unitName_)
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
      .withArguments(unitName_, "replace")
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

}  // namespace Packages
