/*
Created by Connor on 15/06/2026.
Copyright (c) 2026
All rights reserved.
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
