#pragma once
#include "prelude.hpp"

struct ident {
  template <class T>
  T operator()(T x) const { return x; }
};
