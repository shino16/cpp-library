#pragma once
#include "dfa.hpp"

namespace dfa {

template <class T>
struct multiple_of : dfa_default {
  T d;
  constexpr multiple_of(T d) : d(d) {}

  using alphabet = char;
  using state = T;
  state init() const { return 0; }
  state next(state s, alphabet a, int) const {
    return (s * 10 + (a - '0')) % d;
  }
  bool accept(state s) const { return s == 0; }
};

}  // namespace dfa
