#pragma once
#include "prelude.hpp"

// pi[i] = max { k : s[0..k) == s[i-k..i) }
template <class It>
vector<int> kmp(It s, It s_last) {
  int n = s_last - s;
  vector<int> pi(n + 1);
  pi[0] = -1;
  int len = 0;
  rep2(i, 1, n) {
    while (len != -1 && s[len] != s[i])
      len = pi[len];
    pi[i + 1] = ++len;
  }
  return pi;
}

template <class It1, class It2>
vector<int> occurences(It1 s, It1 s_last, It2 p, It2 p_last) {
  int n = s_last - s, m = p_last - p;
  auto pi = kmp(p, p_last);
  vector<int> res;
  res.reserve(max(0, n - m + 1));
  int i = 0, len = 0;
  while (i < n - m + 1) {
    while (len < m && s[i + len] == p[len]) len++;
    if (len == m) res.push_back(i);
    i += len - pi[len];
    len = pi[len] == -1 ? 0 : pi[len];
  }
  return res;
}
