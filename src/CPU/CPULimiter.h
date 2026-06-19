/*
Created by Connor on 15/06/2026.
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

#ifndef MAINTENANCED_CPULIMITER_H
#define MAINTENANCED_CPULIMITER_H

namespace CPU {

class CPULimiter {
 public:
  static bool setCPULimit(int khz);
  static bool restoreCPULimit();
};

}  // namespace CPU

#endif  // MAINTENANCED_CPULIMITER_H
