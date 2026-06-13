/*
Created by Connor on 01/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#include "DisplayController.h"

#include "HyprlandBackend.h"
#include "KDEBackend.h"
#include "SwayBackend.h"
#include "X11Backend.h"

namespace Display {

DisplayController::DisplayController() { backend = createBackend(); }

DisplayController::~DisplayController() = default;

bool DisplayController::screenOn() {
  if (!backend) return false;
  return backend->screenOn();
}
bool DisplayController::screenOff() {
  if (!backend) return false;
  return backend->screenOff();
}
std::string DisplayController::backendName() const {
  if (!backend) return "None";
  return backend->name();
}

std::unique_ptr<DisplayBackend> DisplayController::createBackend() {
  const char* session = std::getenv("XDG_SESSION_TYPE");
  const char* desktop = std::getenv("XDG_CURRENT_DESKTOP");

  std::string s = session ? session : "";
  std::string d = desktop ? desktop : "";

  // Hyprland
  if (d.find("Hyprland") != std::string::npos) {
    return std::make_unique<HyprlandBackend>();
  }

  // KDE
  if (d.find("KDE") != std::string::npos) {
    return std::make_unique<KDEBackend>();
  }

  // Sway
  if (d.find("Sway") != std::string::npos) {
    return std::make_unique<SwayBackend>();
  }

  // X11
  if (s.find("x11") != std::string::npos) {
    return std::make_unique<X11Backend>();
  }
}

}  // namespace Display