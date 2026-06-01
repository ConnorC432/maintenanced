/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "PacmanBackend.h"

namespace Packages {
bool PacmanBackend::update() { return system("pacman -Syyu --noconfirm") == 0; }

std::string PacmanBackend::name() const { return "pacman"; }

}  // namespace Packages