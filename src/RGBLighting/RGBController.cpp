/*
Created by Connor on 13/06/2026.
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

#include "RGBController.h"

#include <OpenRGB/Client.hpp>
#include <OpenRGB/Color.hpp>
#include <OpenRGB/DeviceInfo.hpp>
#include <chrono>
#include <thread>

namespace rgb {

RGBController::RGBController(std::string host, int port)
    : host_(std::move(host)), port_(port) {}

bool RGBController::turnOffRGB() {
  orgb::Client client("RGBController");
  orgb::ConnectStatus status = client.connect(host_, port_);
  if (status != orgb::ConnectStatus::Success) {
    return false;
  }

  auto devices = client.requestDeviceList();
  for (const auto& device : devices.devices) {
    if (const auto* directMode = device.findMode("Direct")) {
      client.changeMode(device, *directMode);
      delay();
    }

    client.setDeviceColor(device, orgb::Color::Black);
    delay();
  }

  return true;
}
void RGBController::delay() const {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
}  // namespace rgb
