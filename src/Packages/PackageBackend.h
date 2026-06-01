/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_PACKAGEBACKEND_H
#define MAINTENANCED_PACKAGEBACKEND_H

#include <string>

namespace Packages {
class PackageBackend {
 public:
  virtual ~PackageBackend() = default;
  virtual bool update() = 0;
  virtual std::string name() const = 0;
};
}  // namespace Packages

#endif  // MAINTENANCED_PACKAGEBACKEND_H
