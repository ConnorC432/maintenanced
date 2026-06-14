/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "HyprlandBackend.h"

namespace Display {
bool HyprlandBackend::screenOn() {
  return system("hyprctl dispatch dpms on") == 0;
}
bool HyprlandBackend::screenOff() {
  return system("hyprctl dispatch dpms off") == 0;
}
std::string HyprlandBackend::name() const { return "Hyprland"; }
}  // namespace Display
