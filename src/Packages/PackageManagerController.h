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

#include "PackageBackend.h"

namespace Packages {

class PackageBackend;

class PackageManagerController {
 public:
  PackageManagerController();

  bool update();

  [[nodiscard]] std::string backendName() const;

 private:
  std::vector<std::unique_ptr<PackageBackend>> backends;
  std::vector<std::unique_ptr<PackageBackend>> findBackends();;
};

}  // namespace Packages

#endif  // MAINTENANCED_PACKAGEMANAGERCONTROLLER_H
