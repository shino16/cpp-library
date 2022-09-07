#pragma once
#include "bit/ctz.hpp"
#include "util/rand.hpp"

template <class T>
optional<T> mod_sqrt(T a) {
  // Tonelli-Shanks
  if (T::mod() <= 2) return a;
  if (a == T(0)) return T(0);
  if (a.pow((T::mod() - 1) / 2) == -1) return nullopt;
  int s = ctz(T::mod() - 1);
  int q = (T::mod() - 1) >> s;
  T x = a.pow((q + 1) / 2);
  T b = rand32();
  while (b.pow((T::mod() - 1) / 2) != -1) b = rand32();
  b = b.pow(q);
  T ia = a.inv();
  s -= 2;
  for (T e = ia * x * x; e != 1; b *= b, s--) {
    if (e.pow(1 << s) != 1) x *= b, e = ia * x * x;
  }
  return x;
}
