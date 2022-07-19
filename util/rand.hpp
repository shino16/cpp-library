#pragma once
#include "prelude.hpp"

unsigned rand32() {
  static unsigned x = chrono::steady_clock::now().time_since_epoch().count();
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}
