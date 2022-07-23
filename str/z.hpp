#pragma once
#include "prelude.hpp"

template <class It>
vector<int> z_algo(It first, It last) {
  int n = last - first;
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(z[i - l], r - i);
    while (i + z[i] < n && first[z[i]] == first[i + z[i]]) z[i]++;
    if (r < i + z[i]) l = i, r = i + z[i];
  }
  return z;
}

template <class It1, class It2,
          class T = typename iterator_traits<It1>::value_type>
vector<int> occurences(It1 s_first, It1 s_last, It2 p_first, It2 p_last,
                       T sep = '$') {
  int n = s_last - s_first, m = p_last - p_first;
  vector<typename iterator_traits<It1>::value_type> s(n + m + 1);
  copy(p_first, p_last, s.begin());
  s[m] = sep;
  copy(s_first, s_last, s.begin() + m + 1);
  auto z = z_algo(all(s));
  vector<int> res;
  res.reserve(m - n + 1);
  rep(i, n) if (z[m + 1 + i] == n) res.push_back(i);
  return res;
}
