/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
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
