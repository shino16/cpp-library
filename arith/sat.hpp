#pragma once
#include "prelude.hpp"

template <class T, class U>
auto sat_add(T a, U b) {
  using V = common_type_t<T, U>;
  V res;
  return __builtin_add_overflow((V)a, (V)b, &res)
             ? (a < 0 ? numeric_limits<T>::min() : numeric_limits<T>::max())
             : res;
}
template <class T, class U>
auto sat_sub(T a, U b) {
  using V = common_type_t<T, U>;
  V res;
  return __builtin_sub_overflow((V)a, (V)b, &res)
             ? (a < 0 ? numeric_limits<T>::min() : numeric_limits<T>::max())
             : res;
}
template <class T, class U>
auto sat_mul(T a, U b) {
  using V = common_type_t<T, U>;
  V res;
  return __builtin_mul_overflow((V)a, (V)b, &res)
             ? ((a < 0) == (b < 0) ? numeric_limits<T>::max()
                                   : numeric_limits<T>::min())
             : res;
}
