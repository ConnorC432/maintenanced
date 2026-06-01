/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "AptBackend.h"

namespace Packages {
bool AptBackend::update() {
  return system("apt update && apt upgrade -y") == 0;
}
std::string AptBackend::name() const { return "apt"; }
}  // namespace Packages