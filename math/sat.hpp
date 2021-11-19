#pragma once
#include "prelude.hpp"

template <class T> T satadd(T a, T b) {
  T res; return __builtin_add_overflow(a, b, &res) ? (a < 0 ? numeric_limits<T>::min() : numeric_limits<T>::max()) : res;
}
template <class T> T satsub(T a, T b) {
  T res; return __builtin_sub_overflow(a, b, &res) ? (a < 0 ? numeric_limits<T>::min() : numeric_limits<T>::max()) : res;
}
template <class T> T satmul(T a, T b) {
  T res; return __builtin_mul_overflow(a, b, &res) ? ((a<0) == (b<0) ? numeric_limits<T>::max() : numeric_limits<T>::min()) : res;
}
