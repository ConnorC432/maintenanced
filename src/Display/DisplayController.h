/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_DISPLAYCONTROLLER_H
#define MAINTENANCED_DISPLAYCONTROLLER_H

#include <memory>
#include <string>

namespace Display {

class DisplayBackend;

class DisplayController {
 public:
  DisplayController();
  ~DisplayController();

  bool screenOn();
  bool screenOff();

  [[nodiscard]] std::string backendName() const;

 private:
  std::unique_ptr<DisplayBackend> backend;

  std::unique_ptr<DisplayBackend> createBackend();
};

}  // namespace Display

#endif  // MAINTENANCED_DISPLAYCONTROLLER_H
