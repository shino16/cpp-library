#pragma once
#include "prelude.hpp"

template <class T, T val>
struct constant {
  constexpr T operator()() const { return val; }
};
