/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_PACMANBACKEND_H
#define MAINTENANCED_PACMANBACKEND_H

#include "PackageBackend.h"

namespace Packages {

class PacmanBackend : public PackageBackend {
 public:
  bool update() override;
  std::string name() const override;
};

}  // namespace Packages

#endif  // MAINTENANCED_PACMANBACKEND_H
