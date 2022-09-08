#pragma once
#include "prelude.hpp"

// z[i] = max { k : s[..k) == s[i..i+k) }
template <class It>
vector<int> z_algo(It s, It s_last) {
  int n = s_last - s;
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(z[i - l], r - i);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (r < i + z[i]) l = i, r = i + z[i];
  }
  return z;
}
