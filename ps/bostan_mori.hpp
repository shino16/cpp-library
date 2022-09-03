#pragma once
#include "ps/fft.hpp"

template <class T>
T bostan_mori(vector<T> a, vector<T> b, ll n) {
  int k = max(2, 1 + atcoder::internal::ceil_pow2(max(a.size(), b.size())));
  int d = 1 << k, half = d / 2;
  a.resize(d), b.resize(d);
  fft(a), fft(b);

  const T w =
      T(atcoder::internal::primitive_root<T::mod()>).pow((T::mod() - 1) >> k);
  vector<T> z(half);
  z[0] = T(d).inv() * 2;
  rep(i, half - 1) z[i + 1] = z[i] * w;
  vector<T> iw(k - 1), y(half);  // bit-reversed
  iw[k - 2] = w.inv();
  repr(i, k - 2) iw[i] = iw[i + 1] * iw[i + 1];
  y[0] = 1;
  rep(t, k - 1) rep(i, 1 << t) y[i | 1 << t] = y[i] * iw[t];

  auto dbl = [&](vector<T>& v) {
    copy(v.begin(), v.begin() + half, v.begin() + half);
    ifft(v.begin() + half, v.end());
    rep(i, half) v[i + half] *= z[i];
    fft(v.begin() + half, v.end());
  };

  T c = 1;
  while (true) {
    rep(i, d) a[i] *= b[i ^ 1];
    if (n & 1)
      rep(i, half) a[i] = (a[i << 1] - a[i << 1 | 1]) * y[i];
    else
      rep(i, half) a[i] = a[i << 1] + a[i << 1 | 1];
    if (n == 1) {
      return accumulate(a.begin(), a.begin() + half, T(0)) / (c * d);
    }
    dbl(a);
    rep(i, half) b[i] = b[i << 1] * b[i << 1 | 1];
    dbl(b);
    n >>= 1, c *= 2;
  }
}
