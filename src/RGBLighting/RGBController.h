/*
Created by Connor on 13/06/2026.
Copyright (c) 2026
All rights reserved.
*/

#ifndef MAINTENANCED_RGBCONTROLLER_H
#define MAINTENANCED_RGBCONTROLLER_H

#include <string>

namespace rgb {

class RGBController {

public:
  explicit RGBController(
    std::string host = "127.0.0.1",
    int port = 6742);

  bool turnOffRGB();

private:
  std::string host_;
  int port_;

  void delay() const;
};

}  // namespace rgb

#endif  // MAINTENANCED_RGBCONTROLLER_H
