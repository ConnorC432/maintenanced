/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "SwayBackend.h"

namespace Display {
bool SwayBackend::screenOn() {
  return system("swaymsg output '*' dpms on") == 0;
}

bool SwayBackend::screenOff() {
  return system("swaymsg output '*' dpms off") == 0;
}

std::string SwayBackend::name() const { return "Sway"; }
}  // namespace Display