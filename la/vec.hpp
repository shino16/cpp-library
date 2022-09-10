#pragma once
#include "prelude.hpp"

template <class T, class U, class F, size_t... Is>
void zip_with_impl(T&& a, U&& b, F f, index_sequence<Is...>) {
  (f(get<Is>(a), get<Is>(b)), ...);
}

template <class T>
T& operator+=(T& a, const T& b) {
  zip_with_impl(
      a, b, [](auto&& x, auto&& y) { x += y; },
      make_index_sequence<tuple_size_v<T>>{});
  return a;
}

template <class T>
T& operator-=(T& a, const T& b) {
  zip_with_impl(
      a, b, [](auto&& x, auto&& y) { x -= y; },
      make_index_sequence<tuple_size_v<T>>{});
  return a;
}

template <class T>
T operator+(const T& a, const T& b) {
  T c(a);
  c += b;
  return c;
}

template <class T>
T operator-(const T& a, const T& b) {
  T c(a);
  c -= b;
  return c;
}

template <class T>
T dot(const T& a, const T& b) {
  T res(0);
  zip_with_impl(a, b, [&](auto&& x, auto&& y) { res += x * y; });
  return res;
}

template <class T, enable_if_t<tuple_size_v<T> == 2>* = nullptr>
auto det(const T& a, const T& b) {
  return get<0>(a) * get<1>(b) - get<1>(a) * get<0>(b);
}
