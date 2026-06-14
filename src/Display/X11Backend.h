/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_X11BACKEND_H
#define MAINTENANCED_X11BACKEND_H

#include <string>

#include "DisplayBackend.h"

namespace Display {

class X11Backend : public DisplayBackend {
 public:
  bool screenOn() override;
  bool screenOff() override;
  std::string name() const override;
};

}  // namespace Display

#endif  // MAINTENANCED_X11BACKEND_H
