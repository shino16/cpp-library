#pragma once
#include "prelude.hpp"

auto seed() {
  return chrono::steady_clock::now().time_since_epoch().count();
}