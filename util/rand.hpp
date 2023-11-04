#pragma once
#include "util/seed.hpp"

uint32_t rand32() {
  static uint32_t x = seed();
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

uint64_t rand64() {
  return uint64_t(rand32()) << 32 | rand32();
}
