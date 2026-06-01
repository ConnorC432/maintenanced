/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_KDEBACKEND_H
#define MAINTENANCED_KDEBACKEND_H

#include "DisplayBackend.h"

namespace Display {

class KDEBackend : public DisplayBackend {
 public:
  bool screenOn() override;
  bool screenOff() override;
  std::string name() const override;
};

}  // namespace Display

#endif  // MAINTENANCED_KDEBACKEND_H
