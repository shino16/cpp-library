#pragma once
#include "prelude.hpp"

template <class T, T val>
struct constant {
  template <class... Ts>
  constexpr T operator()(Ts&&...) const { return val; }
};
