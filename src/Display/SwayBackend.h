/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
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
