/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "PackageManagerController.h"

#include <fstream>

#include "AptBackend.h"
#include "PacmanBackend.h"

namespace Packages {
PackageManagerController::PackageManagerController() {
  DistroInfo info = determineDistro();
  backend = createBackend(info);
}
bool PackageManagerController::update() {
  if (!backend) return false;
  return backend->update();
}
std::string PackageManagerController::backendName() const {
  if (!backend) return "None";

  // return info.name;
  return backend->name();
}
std::unique_ptr<PackageBackend> PackageManagerController::createBackend(
    const DistroInfo& info) {
  if (info.id.find("arch") != std::string::npos) {
    return std::make_unique<PacmanBackend>();
  }

  if (info.id.find("ubuntu") != std::string::npos) {
    return std::make_unique<AptBackend>();
  }

  // TODO improve fallback
  return std::make_unique<PacmanBackend>();
}

PackageManagerController::DistroInfo
PackageManagerController::determineDistro() {
  std::ifstream file("/etc/os-release");

  DistroInfo info;

  if (!file.is_open()) {
    return info;
  }

  std::string line;

  while (std::getline(file, line)) {
    auto pos = line.find('=');
    if (pos == std::string::npos) continue;

    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);

    // Remove quotes
    if (!value.empty() && value.front() == '"') value.erase(0, 1);
    if (!value.empty() && value.back() == '"') value.pop_back();

    if (key == "ID") {
      info.id = value;
    } else if (key == "NAME") {
      info.name = value;
    }
  }

  return info;
}
}  // namespace Packages
