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

#ifndef MAINTENANCED_DISPLAYBACKEND_H
#define MAINTENANCED_DISPLAYBACKEND_H

#include <string>

namespace Display {

class DisplayBackend {
 public:
  virtual ~DisplayBackend() = default;
  virtual bool screenOn() = 0;
  virtual bool screenOff() = 0;
  virtual std::string name() const = 0;
};
}  // namespace Display

#endif  // MAINTENANCED_DISPLAYBACKEND_H
