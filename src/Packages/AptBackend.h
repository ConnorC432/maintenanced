/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_APTBACKEND_H
#define MAINTENANCED_APTBACKEND_H

#include "PackageBackend.h"

namespace Packages {

class AptBackend : public PackageBackend {
 public:
  bool update() override;
  std::string name() const override;
};

}  // namespace Packages

#endif  // MAINTENANCED_APTBACKEND_H
