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

#ifndef MAINTENANCED_PACKAGEMANAGERBACKEND_H
#define MAINTENANCED_PACKAGEMANAGERBACKEND_H

#include <string>

namespace Packages {

class PackageManagerBackend {
 public:
  PackageManagerBackend(std::string unitName, std::string backendName);

  bool update();

  [[nodiscard]] std::string backendName() const;

 private:
  std::string unitName_;
  std::string backendName_;
};

}  // namespace Packages

#endif  // MAINTENANCED_PACKAGEMANAGERBACKEND_H
