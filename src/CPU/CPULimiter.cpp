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

#include "CPULimiter.h"

#include <filesystem>
#include <fstream>

namespace CPU {
bool CPULimiter::setCPULimit(int khz) {
  namespace fs = std::filesystem;

  bool success = false;

  for (const auto& entry : fs::directory_iterator("/sys/devices/system/cpu/")) {
    const auto name = entry.path().filename().string();

    if (name.rfind("cpu", 0) != 0) {
      continue;
    }

    auto freqFile = entry.path() / "cpufreq/scaling_max_freq";

    if (!fs::exists(freqFile)) {
      continue;
    }

    std::ofstream file(freqFile);

    if (!file) {
      success = true;
      continue;
    }

    file << khz;
  }

  return success;
}
bool CPULimiter::restoreCPULimit() {
  // TODO Implement
  return true;
}
}  // namespace CPU
