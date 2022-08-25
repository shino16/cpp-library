#pragma once
#include "prelude.hpp"

auto seed() {
#if defined(LOCAL) || defined(FIX_SEED)
  return 314169265258979;
#endif
  return chrono::steady_clock::now().time_since_epoch().count();
}
