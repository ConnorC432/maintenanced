/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "PackageManagerController.h"

#include <fstream>

#include "PackageManagerBackend.h"

namespace Packages {

static bool commandExists(const std::string& command) {
  std::string check = "command -v " + command + " >/dev/null 2>&1";
  return std::system(check.c_str()) == 0;
}

PackageManagerController::PackageManagerController() {
  backends = findBackends();
}

bool PackageManagerController::update() const {
  if (backends.empty()) return false;

  bool success = false;

  for (const auto& backend : backends) {
    if (backend->update()) {
      success = true;
    }
  }

  return success;
}

std::string PackageManagerController::backendName() const {
  if (backends.empty()) return "None";

  std::string names;

  for (const auto& backend : backends) {
    names += backend->backendName() + ", ";
  }

  return names;
}

std::vector<std::unique_ptr<PackageManagerBackend>>
PackageManagerController::findBackends() {
  std::vector<std::unique_ptr<PackageManagerBackend>> foundBackends;

  if (commandExists("apt")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-apt.service", "apt"));
  }

  if (commandExists("pacman")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-pacman.service", "pacman"));
  }

  if (commandExists("apk")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-apk.service", "apk"));
  }

  if (commandExists("brew")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-brew.service", "brew"));
  }

  if (commandExists("dnf")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-dnf.service", "dnf"));
  } else if (commandExists("yum")) {
    // No need to use yum if dnf is available
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-yum.service", "yum"));
  }

  if (commandExists("emerge")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-emerge.service", "emerge"));
  }

  if (commandExists("flatpak")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-flatpak.service", "flatpak"));
  }

  if (commandExists("snap")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-snap.service", "snap"));
  }

  if (commandExists("xbps-install")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-xbps.service", "xbps"));
  }

  if (commandExists("zypper")) {
    foundBackends.push_back(std::make_unique<PackageManagerBackend>(
        "maintenanced-zypper.service", "zypper"));
  }

  return foundBackends;
}
}  // namespace Packages
