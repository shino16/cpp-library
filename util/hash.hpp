#pragma once
#include "util/rand.hpp"

[[gnu::const]] uint64_t splitmix64(uint64_t x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

template <class T, class = void>
struct anti_hack_hash;

template <class T>
struct anti_hack_hash<T, enable_if_t<is_convertible_v<T, uint64_t>>> {
  size_t operator()(T x) const {
    static const uint64_t ofs = seed();
    return splitmix64((uint64_t)x + ofs);
  }
};

template <class T>
struct anti_hack_hash<T, void_t<decltype(tuple_size<T>::value)>> {
  size_t operator()(const T& x) const {
    return hash_impl(x, make_index_sequence<tuple_size_v<T>>{});
  }

 private:
  static auto make_seed() {
    array<uint64_t, tuple_size_v<T>> res;
    res[0] = seed();
    rep(i, tuple_size_v<T> - 1) res[i + 1] = splitmix64(res[i]) + seed();
    return res;
  }
  template <size_t... Is>
  static size_t hash_impl(const T& x, index_sequence<Is...>) {
    size_t res = 0;
    ((void)(res = splitmix64(
                res + anti_hack_hash<tuple_element_t<Is, T>>{}(get<Is>(x)))),
     ...);
    return res;
  }
};
