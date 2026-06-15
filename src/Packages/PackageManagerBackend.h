/*
Created by Connor on 15/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_PACKAGEMANAGERBACKEND_H
#define MAINTENANCED_PACKAGEMANAGERBACKEND_H

#include <string>

namespace Packages {

class PackageManagerBackend {
 public:
  PackageManagerBackend(std::string unitName, std::string backendName);

  bool update();

  [[nodiscard]] std::string backendName() const;

private:
  std::string unitName_;
  std::string backendName_;
};

}  // namespace Packages

#endif  // MAINTENANCED_PACKAGEMANAGERBACKEND_H
