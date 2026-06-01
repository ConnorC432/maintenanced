/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "X11Backend.h"

namespace Display {
bool X11Backend::screenOn() { return system("xset dpms force on") == 0; }

bool X11Backend::screenOff() { return system("xset dpms force off") == 0; }

std::string X11Backend::name() const { return "X11"; }
}  // namespace Display