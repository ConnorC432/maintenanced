/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_PACKAGEMANAGERCONTROLLER_H
#define MAINTENANCED_PACKAGEMANAGERCONTROLLER_H

#include <memory>
#include <string>
#include <vector>

#include "PackageManagerBackend.h"

namespace Packages {

class PackageManagerBackend;

class PackageManagerController {
 public:
  PackageManagerController();

  bool update() const;

  [[nodiscard]] std::string backendName() const;

 private:
  std::vector<std::unique_ptr<PackageManagerBackend>> backends;
  static std::vector<std::unique_ptr<PackageManagerBackend>> findBackends();
  ;
};

}  // namespace Packages

#endif  // MAINTENANCED_PACKAGEMANAGERCONTROLLER_H
