/*
Created by Connor on 15/06/2026.
Copyright (c) 2026
All rights reserved.
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
