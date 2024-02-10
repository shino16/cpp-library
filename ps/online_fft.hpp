#pragma once

#include "ps/fft.hpp"

template <class T>
struct online_fft {
 public:
  int size() const { return a.size(); }
  const vector<T>& get() const& { return c; }
  const vector<T>& finalize() {
    while (a.size() & (a.size() + 1)) add(0, 0);
    c.pop_back();
    return c;
  }
  T add(T ai, T bi) {
    a.push_back(ai);
    b.push_back(bi);
    c.push_back(0);
    c.push_back(0);
    int n = a.size();
    int max_m = (n + 1) & -(n + 1);
    for (int m = 1; m <= max_m && m <= n; m *= 2) {
      calc(m - 1, m * 2 - 1, n - m, n);
      if (m * 2 - 1 != n) calc(n - m, n, m - 1, m * 2 - 1);
    }
    return c[a.size() - 1];
  }

 private:
  vector<T> a, b, c;
  void calc(int al, int ar, int bl, int br) {
    auto cx = atcoder::convolution(
        vector(a.begin() + al, a.begin() + ar),
        vector(b.begin() + bl, b.begin() + br));
    rep(i, cx.size()) c[al + bl + i] += cx[i];
  }
};
