/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "X11Backend.h"

namespace Display {
bool X11Backend::screenOn() { return system("xset dpms force on") == 0; }

bool X11Backend::screenOff() { return system("xset dpms force off") == 0; }

std::string X11Backend::name() const { return "X11"; }
}  // namespace Display
