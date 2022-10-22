#pragma once
#include "prelude.hpp"

template <class T, class U, class F, size_t... Is>
void zip_with_impl(T&& a, U&& b, F f, index_sequence<Is...>) {
  (f(get<Is>(a), get<Is>(b)), ...);
}

template <class T, class U, class F>
void zip_with(T&& a, U&& b, F f) {
  zip_with_impl(
      forward<T>(a), forward<U>(b), f,
      make_index_sequence<tuple_size_v<decay_t<T>>>{});
}

template <
    class T, class U,
    enable_if_t<tuple_size<T>::value == tuple_size<U>::value>* = nullptr>
T& operator+=(T& a, const U& b) {
  zip_with(a, b, [](auto&& x, auto&& y) { x += y; });
  return a;
}

template <
    class T, class U,
    enable_if_t<tuple_size<T>::value == tuple_size<U>::value>* = nullptr>
T& operator-=(T& a, const U& b) {
  zip_with(a, b, [](auto&& x, auto&& y) { x -= y; });
  return a;
}

template <
    class T, class U,
    enable_if_t<tuple_size<T>::value == tuple_size<U>::value>* = nullptr>
T operator+(const T& a, const U& b) {
  T c(a);
  c += b;
  return c;
}

template <
    class T, class U,
    enable_if_t<tuple_size<T>::value == tuple_size<U>::value>* = nullptr>
T operator-(const T& a, const U& b) {
  T c(a);
  c -= b;
  return c;
}

template <class T, class E = tuple_element_t<0, T>>
E dot(const T& a, const T& b) {
  E res(0);
  zip_with(a, b, [&](auto&& x, auto&& y) { res += x * y; });
  return res;
}

template <class T, enable_if_t<tuple_size_v<T> == 2>* = nullptr>
auto det(const T& a, const T& b) {
  return get<0>(a) * get<1>(b) - get<1>(a) * get<0>(b);
}
