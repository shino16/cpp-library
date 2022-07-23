#pragma once
#include "prelude.hpp"

template <class It>
vector<int> kmp(It first, It last) {
  int n = last - first;
  vector<int> pi(n + 1);
  pi[0] = -1;
  rep2(i, 1, n) {
    int len = pi[i];
    while (s[len] != s[i]) len = pi[len];
    pi[i + 1] = len + 1;
  }
  return pi;
}
