#pragma once
#include "ps/fps.hpp"

auto div(auto a, auto b) {
  int n = a.size() - b.size() + 1;
  reverse(all(a));
  a.resize(n);
  reverse(all(b));
  auto c = a.conv(b.inv(n));
  c.resize(n);
  reverse(all(c));
  return c;
}

template <class T>
T bostan_mori(formal_power_series<T> a, formal_power_series<T> b, ll n) {
  a.trunc(), b.trunc();
  T ofs = 0;
  if (a.size() >= b.size()) {
    auto c = div(a, b);
    if (n < c.size()) ofs += c[n];
    a -= move(c).conv(b);
    a.resize(b.size());
    a.trunc();
  }
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
    n >>= 1, c *= 2;
    rep(i, half) b[i] = b[i << 1] * b[i << 1 | 1];
    if (n < half) break;
    dbl(a);
    dbl(b);
  }
  a.resize(half);
  b.resize(half);
  ifft(a), ifft(b);
  return convolution(move(a), inv(move(b)))[n] / c + ofs;
}

template <class T>
T bostan_mori(vector<T> a, vector<T> b, ll n) {
  return bostan_mori(
      formal_power_series<T>(move(a)), formal_power_series<T>(move(b)), n);
}
