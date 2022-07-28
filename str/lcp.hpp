#pragma once
#include "str/suffix_array.hpp"

template <class It1, class It2>
vector<int> longest_common_prefix(It1 s, It1 s_last, It2 p, It2 p_last) {
  int n = s_last - s;
  vector<int> rank(n), lcp(n-1);
  rep(i, n) rank[p[i]] = i;
  for (int i = 0, len = 0; i < n; i++, len -= len != 0) {
    if (rank[i] == n-1) {
      len = 0;
      continue;
    }
    int j = p[rank[i] + 1];
    while (i+len < n && j+len < n && s[i+len] == s[j+len]) len++;
    lcp[rank[i]] = len;
  }
  return lcp;
}
