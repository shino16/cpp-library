#pragma once
#include "prelude.hpp"

struct noisy {
  noisy() = default;
  noisy(const noisy&) { cout << "copy ctor" << endl; }
  noisy(noisy&&) { cout << "move ctor" << endl; }
  noisy& operator=(const noisy&) { cout << "copy assign" << endl; return *this; }
  noisy& operator=(noisy&&) { cout << "move assign" << endl; return *this; }
};
