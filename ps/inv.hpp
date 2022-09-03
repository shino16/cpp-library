#pragma once
#include "ps/fft.hpp"

template <class T>
vector<T> inv(const vector<T>& f, int deg = -1) {
  assert(f[0] != 0);
  if (deg == -1) deg = f.size();
  int z = 1 << atcoder::internal::ceil_pow2(deg);
  vector<T> g = {1 / f[0]}, gfft(1);
  vector<T> h;
  g.reserve(z), gfft.reserve(z), h.reserve(z);
  const T i4 = T(4).inv();
  T imm4 = i4;
  for (int m = 1; m < z; m <<= 1, imm4 *= i4) {
    h.assign(f.begin(), f.begin() + min((int)f.size(), m * 2));
    copy(all(g), gfft.begin());
    fft(h, m * 2), fft(gfft, m * 2);
    rep(i, m * 2) h[i] *= gfft[i];
    ifft(h), fill(h.begin(), h.begin() + m, 0), fft(h);
    rep(i, m * 2) h[i] *= -gfft[i];
    ifft(h);
    rep2(i, m, m * 2) g.push_back(h[i] * imm4);
  }
  g.resize(deg);
  return g;
}
