#pragma once

#include "prelude.hpp"

template <class T, class U>
common_type_t<T, U> div_floor(T a, U b) {
  auto q = a / b, r = a % b;
  return q - ((r > 0 && b < 0) || (r < 0 && b > 0));
}

template <class T, class U>
common_type_t<T, U> div_ceil(T a, U b) {
  auto q = a / b, r = a % b;
  return q + ((r > 0 && b > 0) || (r < 0 && b < 0));
}

template <class T, class U>
common_type_t<T, U> rem(T a, U b) {
  auto r = a % b;
  return r >= 0 ? r : r + abs(b);
}
