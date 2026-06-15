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

static bool commandExists(const std::string& command) {
  std::string check = "command -v " + command + " >/dev/null 2>&1";
  return std::system(check.c_str()) == 0;
}

PackageManagerController::PackageManagerController() {
  backends = findBackends();
}

bool PackageManagerController::update(){
  if (backends.empty()) return false;

  bool success = false;

  for (const auto& backend : backends) {
    if (backend->update()) {
      success = true;
    }
  }

  return success;
}

std::string PackageManagerController::backendName() const{
  if (backends.empty()) return "None";

  std::string names;

  for (const auto& backend : backends) {
    names += backend->name() + ", ";
  }

  return names;
}

std::vector<std::unique_ptr<PackageBackend>> PackageManagerController::findBackends() {
  std::vector<std::unique_ptr<PackageBackend>> foundBackends;

  if (commandExists("apt")) {
    foundBackends.push_back(std::make_unique<AptBackend>());
  }

  if (commandExists("pacman")) {
    foundBackends.push_back(std::make_unique<PacmanBackend>());
  }

  return foundBackends;
}
}  // namespace Packages
