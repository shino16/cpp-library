#pragma once
#include "prelude.hpp"

// p[i] = starting position of i-th smallest shift
template <class It>
vector<int> sort_cyclic_shifts(It s, It s_last, int lim = 256) {
  int n = s_last - s;
  // c[i] = ordered tag of i-shift
  vector<int> p(n), p2(n), c(n), c2(n), cnt(max(n, lim), 0);

  rep(i, n) cnt[s[i]]++;
  rep(i, lim - 1) cnt[i + 1] += cnt[i];
  repr(i, n) p[--cnt[s[i]]] = i;
  int k = 0;
  rep(i, n - 1) c[p[i + 1]] = k += s[p[i]] != s[p[i + 1]];
  k++;

  for (int w = 1; w < n; w <<= 1) {
    rep(i, n) {
      int t = p[i] - w;
      p2[i] = t < 0 ? t + n : t;
    }
    fill(cnt.begin(), cnt.begin() + k, 0);
    rep(i, n) cnt[c[i]]++;
    rep(i, k - 1) cnt[i + 1] += cnt[i];
    repr(i, n) p[--cnt[c[p2[i]]]] = p2[i];
    c[p[0]] = k = 0;
    rep(i, n-1) {
      int piw = p[i] + w >= n ? p[i] + w - n : p[i] + w;
      int pi2w = p[i+1] + w >= n ? p[i+1] + w - n : p[i+1] + w;
      pair<int, int> prv(c[p[i]], c[piw]);
      pair<int, int> nxt(c[p[i + 1]], c[pi2w]);
      c2[p[i+1]] = k += prv != nxt;
    }
    k++;
    swap(c, c2);
  }
  return p;
}
