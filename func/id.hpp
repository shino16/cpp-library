#pragma once
#include "prelude.hpp"

struct identity {
  template <class T>
  T operator()(T x) const { return x; }
};
