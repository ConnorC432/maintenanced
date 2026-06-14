/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "KDEBackend.h"

namespace Display {
bool KDEBackend::screenOn() { return system("kscreen-doctor --dpms off") == 0; }
bool KDEBackend::screenOff() { return system("kscreen-doctor --dpms on") == 0; }
std::string KDEBackend::name() const { return "KDE Plasma"; }
}  // namespace Display
