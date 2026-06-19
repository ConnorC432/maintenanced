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

#ifndef MAINTENANCED_SWAYBACKEND_H
#define MAINTENANCED_SWAYBACKEND_H

#include <string>

#include "DisplayBackend.h"

namespace Display {

class SwayBackend : public DisplayBackend {
 public:
  bool screenOn() override;
  bool screenOff() override;
  std::string name() const override;
};

}  // namespace Display

#endif  // MAINTENANCED_SWAYBACKEND_H
