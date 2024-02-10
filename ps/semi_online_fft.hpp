#pragma once

#include "bit/ilog2.hpp"
#include "ps/fft.hpp"

template <class T>
struct semi_online_fft {
 public:
  semi_online_fft(vector<T> a_ = {T(1)}) : a(move(a_)) {
    int n = bit_ceil(a.size());
    a.resize(n);
    c.resize(n * 2);
  }
  int size() const { return a.size(); }
  const T& operator[](int i) const { return c[i]; }
  const vector<T>& get() const& { return c; }
  const vector<T>& finalize() {
    while (b.size() & (b.size() - 1)) push(0);
    while (b.size() < a.size() / 2) push(0);
    c.pop_back();
    return c;
  }
  T push(T bi) {
    b.push_back(bi);
    if (b.size() >= a.size()) a.resize(a.size() * 2), c.resize(c.size() * 2);
    c[b.size() - 1] += a[0] * bi;
    int n = b.size();
    int max_m = n & -n;
    for (int m = 1; m <= max_m && m <= n; m *= 2) calc(m, m * 2, n - m, n);
    return c[b.size() - 1];
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
